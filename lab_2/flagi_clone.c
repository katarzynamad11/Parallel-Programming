#define _GNU_SOURCE //pozwala na wlaczenie dodatkowych funkcji i rozszerzen, takich jak funkcja clone
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h> //zawiera deklaracje funkcji clone
#include <linux/sched.h>

//#include"pomiar_czasu.h" //dodanie nagłówka

int zmienna_globalna=0; //bedzie modyfikowana przez kazdy watek

#define ROZMIAR_STOSU 143//rozmiar stosu dla kazdego watku na 64 KB

int funkcja_watku(void* argument) {  //funkcja ktora zostanie uruchomiona w kazdym nowym watku
    zmienna_globalna++;

  
}
int main()
{

  void *stos; // zmienna wskaznikowa bedzie uzywana do przechowywania adresu zarezerwowanej pamieci na stos watku
  pid_t pid;
  int i; 
  
  stos = malloc( ROZMIAR_STOSU ); //jesli nie powiedzie sie, malloc zwroci 0, malloc rezerwuje 64KB pamieci
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }
	
	
    
   pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
		

    waitpid(pid, NULL, __WCLONE); //funkcja czeka na zakonczenie watku
 	
  free( stos );
}
