#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size, number;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // określenie poprzednika i następcy
    int prev = (rank - 1 + size) % size;
    int next = (rank + 1) % size;

    if (rank == 0) {
        number = 10; // Inicjalizacja liczby przez proces 0
        printf("Proces %d wysłał liczbę %d do procesu %d.\n", rank, number, next);
        MPI_Send(&number, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Recv(&number, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
        printf("Proces %d odebrał liczbę %d od procesu %d.\n", rank, number, prev);
    } else {
        MPI_Recv(&number, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);
        printf("Proces %d odebrał liczbę %d od procesu %d.\n", rank, number, prev);
        number++;
        printf("Proces %d wysłał liczbę %d do procesu %d.\n", rank, number, next);
        MPI_Send(&number, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

