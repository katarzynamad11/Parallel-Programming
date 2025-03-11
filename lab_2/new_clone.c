#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>

#define ROZMIAR_STOSU 1024*64


int zmienna_globalna = 0;  // zmienna globalna wspoldzielona przez oba watki

// funkcja wykonywana przez watek
int funkcja_watku(void* argument) {
    int zmienna_lokalna = *((int*) argument);
 
    for(int i = 0; i < 100000; i++) {
        zmienna_globalna++;  // zwiekszanie zmiennej globalnej
        zmienna_lokalna++;  // zwiekszanie zmiennej lokalnej
    
}
    printf("zmienna globalna = %d, zmienna lokalna = %d\n", zmienna_globalna, zmienna_lokalna);
    return 0;
}

int main() {


    void *stos1, *stos2;
    pid_t pid1, pid2;
    int i;
    int zmienna_lokalna1 = 0;
    int zmienna_lokalna2 = 0;

    
    stos1 = malloc( ROZMIAR_STOSU );
    stos2 = malloc( ROZMIAR_STOSU );
    
  if (stos1 == 0 || stos2 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }


    pid1 = clone(&funkcja_watku, (void*) stos1 + ROZMIAR_STOSU,
                 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &zmienna_lokalna1);
    
    
    pid2 = clone(&funkcja_watku, (void*) stos2 + ROZMIAR_STOSU,
                 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &zmienna_lokalna2);

  
    waitpid(pid1, NULL, __WCLONE);

   
    waitpid(pid2, NULL, __WCLONE);

 
    printf("Wartości po zakończeniu wątków:\n");
    printf("Zmienna globalna = %d\n", zmienna_globalna);
    printf("Zmienna lokalna 1 = %d\n", zmienna_lokalna1);
    printf("Zmienna lokalna 2 = %d\n", zmienna_lokalna2);


    free(stos1);
    free(stos2);

    return 0;
}

