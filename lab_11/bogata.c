#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_PROCESSES 4

typedef struct {
    int id;
    char imie[20];
    double wartosc;
} Dane;

void wyslij_strukture(Dane* dane, int dest, int tag, MPI_Comm comm) {
    int rozm_pakietu, pozycja = 0;
    void* bufor;
    int rozmiar;


    MPI_Pack_size(1, MPI_INT, comm, &rozmiar);
    rozm_pakietu = rozmiar;
    MPI_Pack_size(20, MPI_CHAR, comm, &rozmiar);
    rozm_pakietu += rozmiar;
    MPI_Pack_size(1, MPI_DOUBLE, comm, &rozmiar);
    rozm_pakietu += rozmiar;

    // alokujemy odpowiedni rozmiar 
    bufor = malloc(rozm_pakietu);

    // pakujemy strukture
    MPI_Pack(&dane->id, 1, MPI_INT, bufor, rozm_pakietu, &pozycja, comm);
    MPI_Pack(dane->imie, 20, MPI_CHAR, bufor, rozm_pakietu, &pozycja, comm);
    MPI_Pack(&dane->wartosc, 1, MPI_DOUBLE, bufor, rozm_pakietu, &pozycja, comm);

    // wysyłamy
    MPI_Send(bufor, pozycja, MPI_PACKED, dest, tag, comm);

    free(bufor);
}

void odbierz_strukture(Dane* dane, int src, int tag, MPI_Comm comm, int rozm_pakietu) {
    MPI_Status status;
    int pozycja = 0;
    void* bufor = malloc(rozm_pakietu);

    // odbieramy
    MPI_Recv(bufor, rozm_pakietu, MPI_PACKED, src, tag, comm, &status);

    // rozpakowujemy strukture
    MPI_Unpack(bufor, rozm_pakietu, &pozycja, &dane->id, 1, MPI_INT, comm);
    MPI_Unpack(bufor, rozm_pakietu, &pozycja, dane->imie, 20, MPI_CHAR, comm);
    MPI_Unpack(bufor, rozm_pakietu, &pozycja, &dane->wartosc, 1, MPI_DOUBLE, comm);

    free(bufor);
}

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("Ten program wymaga co najmniej dwóch procesów.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    Dane dane;
    int rozm_pakietu;

    // Obliczenie rozmiaru pakietu raz na początku
    int rozmiar;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &rozmiar);
    rozm_pakietu = rozmiar;
    MPI_Pack_size(20, MPI_CHAR, MPI_COMM_WORLD, &rozmiar);
    rozm_pakietu += rozmiar;
    MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &rozmiar);
    rozm_pakietu += rozmiar;

    if (rank == 0) {
        // inicjalizacja danych w procesie 0
        dane.id = 1;
        strncpy(dane.imie, "Katarzyna", 20);
        dane.wartosc = 3.14;

        printf("Proces %d wysyła: id=%d, imie=%s, wartosc=%.2f\n", rank, dane.id, dane.imie, dane.wartosc);
        wyslij_strukture(&dane, 1, 0, MPI_COMM_WORLD);
    } else {
        // odbieranie struktury
        odbierz_strukture(&dane, rank - 1, 0, MPI_COMM_WORLD, rozm_pakietu);
        printf("Proces %d otrzymał: id=%d, imie=%s, wartosc=%.2f\n", rank, dane.id, dane.imie, dane.wartosc);

        // modyfikacja danych
        dane.id += 1;
        dane.wartosc *= 2;
        strcat(dane.imie, "_mod");

        // jeśli to nie jest ostatni proces, wysyłamy dalej
        if (rank < size - 1) {
            printf("Proces %d wysyła: id=%d, imie=%s, wartosc=%.2f\n", rank, dane.id, dane.imie, dane.wartosc);
            wyslij_strukture(&dane, rank + 1, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}

