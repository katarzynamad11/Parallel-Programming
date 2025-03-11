#define _GNU_SOURCE //pozwala na wlaczenie dodatkowych funkcji i rozszerzen, takich jak funkcja clone
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h> //zawiera deklaracje funkcji clone
#include <linux/sched.h>

#include"pomiar_czasu.h" //dodanie nagłówka

int zmienna_globalna=0; //bedzie modyfikowana przez kazdy watek

#define ROZMIAR_STOSU 1024*64 //rozmiar stosu dla kazdego watku na 64 KB

int funkcja_watku(void* argument) {  //funkcja ktora zostanie uruchomiona w kazdym nowym watku
    zmienna_globalna++;

   
    char *args[4];
    args[0] = "./zajecia_2"; 
    args[1] = "Katarzyna";  
    args[2] = "Madej";    
    args[3] = NULL;        

   
    int wynik = execv(args[0], args); 
    // exec - mozliwosc uruchomienia innego kodu w procesie potomnym
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
	//inicjuj_czas(); // wywolanie funkcji - trzeba pamietac, że nie liczymy w takim przypadku czasu tworzenia stosu
	
  //for(i=0;i<1000;i++){

    pid = clone( &funkcja_watku, (void *) stos+ROZMIAR_STOSU, 
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
		

//&funkcja_watku - wskaznik na funkcje 
//(void *) stos+ROZMIAR_STOSU- wskaznik na gore stosu/stos przechowywany od konca do poczatku
//CLONE_FS - wspoldzielenie systemu plikow
//CLONE_FILES - wspoldzienie deskryptow plikow
//CLONE_VM - wspoldzenie przestrzeni adresowej
//CLONE_SIGHAN - wspoldzielenie obslugi sygnalow

    waitpid(pid, NULL, __WCLONE); //funkcja czeka na zakonczenie watku
	
 // }
	//drukuj_czas();
  free( stos );
}
