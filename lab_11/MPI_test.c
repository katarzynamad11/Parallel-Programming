/*
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, number;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Proces początkowy
        number = 10;
        printf("Proces początkowy %d wysłał liczbę %d do procesu 1.\n", rank, number);
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank > 0 && rank < size - 1) {
        // Procesy środkowe
        MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        printf("Proces środkowy %d odebrał liczbę %d od procesu %d.\n", rank, number, rank - 1);
        number++;
        MPI_Send(&number, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    } else {
        // Proces końcowy
        MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        printf("Proces końcowy %d odebrał liczbę %d od procesu %d.\n", rank, number, rank - 1);
    }

    MPI_Finalize();
    return 0;
}
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size, number;
    MPI_Status status;

    // Inicjalizacja MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // sprawdzanie, czy mamy wystarczającą liczbę procesów
    if (size < 3) {
        printf("Potrzeba przynajmniej 3 procesów do realizacji sztafety zamkniętej.\n");
        MPI_Finalize();
        return 0;
    }

    // proces początkowy
    if (rank == 0) {
        number = 10; /
        printf("Proces początkowy %d wysłał liczbę %d do procesu 1.\n", rank, number);
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // oczekiwanie na zwrot komunikatu od ostatniego procesu
        MPI_Recv(&number, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
        printf("Proces początkowy %d odebrał liczbę %d od procesu %d.\n", rank, number, size - 1);
    } 
    // procesy środkowe
    else if (rank > 0 && rank < size - 1) {
        MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        printf("Proces środkowy %d odebrał liczbę %d od procesu %d.\n", rank, number, rank - 1);
        number++;
        MPI_Send(&number, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        printf("Proces środkowy %d wysłał liczbę %d do procesu %d.\n", rank, number, rank + 1);
    } 
    // proces końcowy
    else if (rank == size - 1) {
        MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        printf("Proces końcowy %d odebrał liczbę %d od procesu %d.\n", rank, number, rank - 1);
        number++;
        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); // wysłanie z powrotem do procesu początkowego
        printf("Proces końcowy %d wysłał liczbę %d z powrotem do procesu %d.\n", rank, number, 0);
    }

  
    MPI_Finalize();
    return 0;
}



