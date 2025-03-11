#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#define watki 3
#define WYMIAR 10
// dla czytelności wydruku należy użyc klauzuli i dyrektywy ordered
int main ()
{
  double a[WYMIAR][WYMIAR];

  for(int i=0;i<WYMIAR;i++) for(int j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

  // podwójna pętla - sekwencyjnie
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
    for(int j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  omp_set_nested(1);

  // podwójna pętla - docelowo równolegle
  double suma_parallel=0.0; int i,j;
  // reduction - uzyskanie sumy przez klauzule 
  
  /*
  //WERSJA 1
  #pragma omp parallel for ordered default(none) reduction(+:suma_parallel) shared(a) num_threads(watki) schedule (static,2)
  for(i=0;i<WYMIAR;i++) {
  int id_w = omp_get_thread_num();
  #pragma omp ordered
  for(int j=0;j<WYMIAR;j++) {
  suma_parallel += a[i][j];
  // dla dekompozycji 1D
  printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
  }
  #pragma omp ordered
   // dla dekompozycji 2D
  //printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num()); 
    printf("\n"); }
  */
  
  /*
  //WERSJA 2
  #pragma omp ordered
  for(i=0;i<WYMIAR;i++) {
  #pragma omp parallel for ordered default(none) reduction(+:suma_parallel) shared(i, a) num_threads(watki) schedule (dynamic)
  for(int j=0;j<WYMIAR;j++) {
  int id_w = omp_get_thread_num();
  suma_parallel += a[i][j];
  #pragma omp ordered
  // dla dekompozycji 1D
  printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
  // dla dekompozycji 2D
 // printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num()); 
     }printf("\n"); } 
    */
    
    /*
    //WERSJA 3
   #pragma omp parallel for ordered default(none) shared(a, suma_parallel) num_threads(watki) schedule(static)
   for( j=0; j<WYMIAR;j++) {
   double suma_fragmentow = 0.0;
   int id_w = omp_get_thread_num();
   for(int i=0; i<WYMIAR;i++) {
   suma_fragmentow += a[i][j];
   #pragma omp ordered
   {printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num());}
   } printf("\n");
   #pragma omp critical(sum_parallel)
   {suma_parallel += suma_fragmentow;}
   } 	*/
   
   
   
   
  //------------------------------------------------------------------------------------------------------------------- 
   
   // omp_set_nested(1) - zapewnienie zagnieżdżenia obszarów równoległych 
   
   omp_set_nested(1);
   #pragma omp parallel for ordered default(none) reduction(+:suma_parallel) shared(a) schedule(static,2)
   for(i=0;i<WYMIAR;i++) {
   int id_w = omp_get_thread_num(); //numer watku w zewn obszarze
   #pragma omp ordered
   {
   #pragma omp parallel for ordered default(none) reduction(+:suma_parallel) shared(i, a) firstprivate(id_w) schedule(static,2)
   for(int j=0; j<WYMIAR;j++) {
   #pragma omp ordered
   {
   int id_w2 = omp_get_thread_num(); //numer watku w wewn obszarze 
   suma_parallel += a[i][j];
   printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w2,omp_get_thread_num()); 
   }
   }printf("\n");}}
   
   
 
  printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);

}
