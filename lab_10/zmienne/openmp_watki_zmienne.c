#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// Deklaracja zmiennej threadprivate przed funkcją main()
static int f_threadprivate = 0;
#pragma omp threadprivate(f_threadprivate)

int main() {
  
#ifdef _OPENMP
  printf("\nKompilator rozpoznaje dyrektywy OpenMP\n");
#endif

  int liczba_watkow;
  
  int a_shared = 1;
  int b_private = 2;
  int c_firstprivate = 3;
  int e_atomic = 5;
  
  printf("przed wejsciem do obszaru rownoleglego -  nr_threads %d, thread ID %d\n",
         omp_get_num_threads(), omp_get_thread_num());
  printf("\ta_shared \t= %d\n", a_shared);
  printf("\tb_private \t= %d\n", b_private);
  printf("\tc_firstprivate \t= %d\n", c_firstprivate);
  printf("\te_atomic \t= %d\n", e_atomic);
  printf("\tthreadprivate \t= %d\n", f_threadprivate);
  
#pragma omp parallel default(none) shared(a_shared, e_atomic) private(b_private) firstprivate(c_firstprivate)
  {
    int i;
    int d_local_private;
    d_local_private = a_shared + c_firstprivate; // 1 + 3 = 4
    // jak wchodzimy do bloku z 4 watkami, a pozniej tworzymy obszar rownolegly z 10 watkami, zeruje nam reszte ID  
    #pragma omp barrier
    #pragma omp critical
    for (i = 0; i < 10; i++) { // WAR 34 39 RAW 39 59 i WAW 39 39
      a_shared++; // 1 + 4 * 10
    }

    for (i = 0; i < 10; i++) {
      c_firstprivate += omp_get_thread_num(); // 3 + 10 * ID (każdy wątek ma swoją kopię) 
    }

    for (i = 0; i < 10; i++) {
      #pragma omp atomic
      e_atomic += omp_get_thread_num(); // 5 + (10 + 20 + 30) //RAW 48 63 WAW 48 48 WAR 48 48
    }

    f_threadprivate = omp_get_thread_num();

    #pragma omp barrier
    #pragma omp critical
    {
      printf("\nw obszarze równoległym: aktualna liczba watkow %d, moj ID %d\n",
             omp_get_num_threads(), omp_get_thread_num());
      
      printf("\ta_shared \t= %d\n", a_shared);
      printf("\tb_private \t= %d\n", b_private);
      printf("\tc_firstprivate \t= %d\n", c_firstprivate);
      printf("\td_local_private = %d\n", d_local_private);
      printf("\te_atomic \t= %d\n", e_atomic);
    }
  }

  // Drugi obszar równoległy z użyciem f_threadprivate
  #pragma omp parallel default(none) num_threads(10)
  
  {
    printf("\nDrugi obszar rownolegly: aktualna liczba watkow %d, moj ID %d\n",
           omp_get_num_threads(), omp_get_thread_num());
    printf("\tthreadprivate \t= %d\n", f_threadprivate);
  
  
    
    
    
    
    
    //#pragma omp single
/* #pragma omp master */
/*         { */
    
/*           printf("\ninside single: nr_threads %d, thread ID %d\n", */
/*     	     omp_get_num_threads(), omp_get_thread_num()); */
/*           /\* Get environment information *\/ */
/*           int procs = omp_get_num_procs(); */
/*           int nthreads = omp_get_num_threads(); */
/*           int maxt = omp_get_max_threads(); */
/*           int inpar = omp_in_parallel(); */
/*           int dynamic = omp_get_dynamic(); */
/*           int nested = omp_get_nested(); */
    
/*           /\* Print environment information *\/ */
/*           printf("Number of processors = %d\n", procs); */
/*           printf("Number of threads = %d\n", nthreads); */
/*           printf("Max threads = %d\n", maxt); */
/*           printf("In parallel? = %d\n", inpar); */
/*           printf("Dynamic threads enabled? = %d\n", dynamic); */
/*           printf("Nested parallelism supported? = %d\n", nested); */
    
/*         } */
    
  }
  
  printf("po zakonczeniu obszaru rownoleglego:\n");
  printf("\ta_shared \t= %d\n", a_shared);
  printf("\tb_private \t= %d\n", b_private);
  printf("\tc_firstprivate \t= %d\n", c_firstprivate);
  printf("\te_atomic \t= %d\n", e_atomic);
  printf("\tthreadprivate \t= %d\n", f_threadprivate);
  
}
