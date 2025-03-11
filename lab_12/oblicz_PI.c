#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h> // Dodanie biblioteki MPI

#define SCALAR double
//#define SCALAR float

#ifndef M_PI // Standardy C99 i C11 nie wymagają definiowania stałej M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(int argc, char **argv) {
    // Program obliczania przybliżenia PI za pomocą wzoru Leibniza
    // PI = 4 * (1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + ...)

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int max_liczba_wyrazow = 0;
    if (rank == 0) {
        max_liczba_wyrazow = 100000000; 
    }
    // rozsyłanie od procesu A do wszystkich procesow dane
    MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);

	//podzial pracy
    int n = (int)ceil((float)(max_liczba_wyrazow) / size);
    int start = n * rank;
    int end = (n * (rank + 1) < max_liczba_wyrazow) ? n * (rank + 1) : max_liczba_wyrazow;

    SCALAR suma_plus = 0.0;
    SCALAR suma_minus = 0.0;

    for (int i = start; i < end; i++) {
        int j = 1 + 4 * i;
        suma_plus += 1.0 / j;
        suma_minus += 1.0 / (j + 2.0);}
    

    SCALAR pi_approx = 4 * (suma_plus - suma_minus);
    SCALAR res = 0.0;

	//redukcja z zadaną operacją

	//sumuje pi_approx i zbieranie wyników do &res
	int root = 1 ; //odbiorca
    MPI_Allreduce(&pi_approx, &res, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    //MPI_Reduce(&pi_approx, &res, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);
   
   if (rank == 0) {
    printf("PI obliczone przez proces %d: \t\t%20.15lf\n", rank, res);
    printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
} else {
    printf("PI obliczone przez proces %d: \t\t%20.15lf\n", rank, res);
    printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
}


    MPI_Finalize();
    return 0;
}

