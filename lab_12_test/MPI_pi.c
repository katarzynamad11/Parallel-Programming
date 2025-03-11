#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h> // Dodanie biblioteki MPI

#define SCALAR double

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int max_liczba_wyrazow = 0;
    if (rank == 0) {
        max_liczba_wyrazow = 100000000;
    }
    MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int n = (int)ceil((double)max_liczba_wyrazow / (double)size);
    int start = n * rank;
    int end = MAX(n * (rank + 1), max_liczba_wyrazow);
    if (end > max_liczba_wyrazow) {
        end = max_liczba_wyrazow;
    }

    SCALAR suma_plus = 0.0;
    SCALAR suma_minus = 0.0;

    for (int i = start; i < end; i++) {
        int j = 1 + 4 * i;
        suma_plus += 1.0 / j;
        suma_minus += 1.0 / (j + 2.0);
    }

    SCALAR pi_approx = 4 * (suma_plus - suma_minus);
    SCALAR res = 0.0;

    MPI_Allreduce(&pi_approx, &res, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    printf("Proces %d: PI obliczone: \t%20.15lf\n", rank, res);
    if (rank == 0) {
        printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
    }

    MPI_Finalize();
    return 0;
}

