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


void stworz_typ_MPI(Dane* dane, MPI_Datatype* MPI_Dane_Type) {
   
    int liczba_pol = 3;
    MPI_Datatype typy_pol[3] = {MPI_INT, MPI_CHAR, MPI_DOUBLE};

 
    int dlugosci_pol[3] = {1, 20, 1};

    MPI_Aint adres_poczatkowy, adresy_pol[3];
    
    MPI_Get_address(dane, &adres_poczatkowy); // pobieram adresy pamieci 
    MPI_Get_address(&dane->id, &adresy_pol[0]);
    MPI_Get_address(&dane->imie, &adresy_pol[1]);
    MPI_Get_address(&dane->wartosc, &adresy_pol[2]);

	MPI_Aint przesuniecia[3];
	for (int i =0 ; i< 3; i++) {
	przesuniecia[i] = adresy_pol[i]-adres_poczatkowy;
	} 
    MPI_Type_create_struct(liczba_pol, dlugosci_pol, przesuniecia, typy_pol, MPI_Dane_Type);
    MPI_Type_commit(MPI_Dane_Type);
}

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Datatype MPI_Dane_Type;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
   
    Dane dane;
    stworz_typ_MPI(&dane, &MPI_Dane_Type);

    if (rank == 0) {
        
        dane.id = 1;
        strncpy(dane.imie, "Katarzyna", 20);
        dane.wartosc = 3.14;

        printf("Proces %d wysyła: id=%d, imie=%s, wartosc=%.2f\n", rank, dane.id, dane.imie, dane.wartosc);
        MPI_Send(&dane, 1, MPI_Dane_Type, 1, 0, MPI_COMM_WORLD);
    } else {
       
        MPI_Status status;
        MPI_Recv(&dane, 1, MPI_Dane_Type, rank - 1, 0, MPI_COMM_WORLD, &status);
        printf("Proces %d otrzymał: id=%d, imie=%s, wartosc=%.2f\n", rank, dane.id, dane.imie, dane.wartosc);

        // modyfikacja danych
        dane.id += 1;
        dane.wartosc *= 2;
        strcat(dane.imie, "_mod");

        // jeśli to nie jest ostatni proces, wysyłamy dalej
        if (rank < size - 1) {
            printf("Proces %d wysyła: id=%d, imie=%s, wartosc=%.2f\n", rank, dane.id, dane.imie, dane.wartosc);
            MPI_Send(&dane, 1, MPI_Dane_Type, rank + 1, 0, MPI_COMM_WORLD);
        }
    }

 
    MPI_Type_free(&MPI_Dane_Type);
    MPI_Finalize();
    return 0;
}

