#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
//export OMP_NUM_THREADS=4
#define WYMIAR 18
#define watki 4
int main ()
{
	omp_set_num_threads(4);
  double a[WYMIAR];
// bez klauzuli schedule- z liczba watkow sterowana przez wartosc zmiennej srodowiskowej omp_num_threads
// klauzula default - wymuszenie jawnego ustalenia charakteru zmiennych 
// klauzula reduction - sterowanie uzyskanym wynikiem suma_parallel, kazdy watek bedzie mial własną kopie zmiennej
// shared: zmienna a jest wspolna dla wszystkich watkow
// klauzula ordered - cel: wymuszenie kolejności wykonywania operacij - w standardowych obliczeniach usuwamy 
//1 - uruchamiamy dla 4 wątkow
#pragma omp  parallel for default(none) shared(a)
  for(int i=0;i<WYMIAR;i++) a[i]=1.02*i;

  // pętla sekwencyjna
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
      suma += a[i];
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  // pętla do modyfikacji - docelowo równoległa w OpenMP
  double suma_parallel=0.0;
  // ustawienie klauzuli num_threads
//#pragma omp parallel for ordered default(none) reduction(+:suma_parallel) shared(a) num_threads(watki)
#pragma omp parallel for ordered default(none) reduction(+:suma_parallel) shared(a) num_threads(watki) schedule (dynamic)
  for(int i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
    // ...
#pragma omp ordered
      suma_parallel += a[i];
      // ...
#pragma omp ordered
      printf("a[%2d]->W_%1d  \n",i,id_w); 
  }

  printf("\nSuma wyrazów tablicy równolegle (z klauzulą - ....: %lf\n",
	 suma_parallel);

}
