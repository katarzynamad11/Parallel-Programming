#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/
int my_read_lock_lock(cz_t* cz_p){ //chce_czytac()

pthread_rwlock_rdlock(&cz_p->rwlock);

	
  cz_p->l_c++;
  
  
  
  
  
  if (cz_p->l_p >0 || cz_p->l_p < 0|| cz_p->l_c <0) { // sprawdzam bledy, nie mogą być liczby ujemny
  printf( "Blad w liczbie pisarzy/czytelnikow\n"); }
  
}


int my_read_lock_unlock(cz_t* cz_p){ //koniec_czytania()
  
  cz_p->l_c--;
  pthread_rwlock_unlock(&cz_p->rwlock); }



int my_write_lock_lock(cz_t* cz_p){ //chce_pisac() 
  pthread_rwlock_wrlock(&cz_p->rwlock);
 
  
  if (cz_p->l_p < 0 || cz_p->l_p > 1|| cz_p->l_c <0 || cz_p->l_c >0) { 
  printf( "Blad w liczbie pisarzy/czytelnikow\n"); }

}


int my_write_lock_unlock(cz_t* cz_p){ //koniec_pisania()
	
   pthread_rwlock_unlock(&cz_p->rwlock);
}

void inicjuj(cz_t* cz_p){

  cz_p->l_p = 0;
  cz_p->l_c = 0;  
  cz_p->l_wait_p= 0;
  cz_p->l_wait_c= 0;  
  pthread_mutex_init(&cz_p->mutex, NULL);
  pthread_cond_init(&cz_p->czytelnicy, NULL);
  pthread_cond_init(&cz_p->pisarze, NULL);
  pthread_rwlock_init(&cz_p->rwlock, NULL);

}

void czytam(cz_t* cz_p){


cz_p->l_wait_p--;
// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
//  printf("\t\t\t\t\tczytam:  l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p); 
// sprawdzenie warunku poprawności i ewentualny exit
// warunek:
  if( cz_p->l_p>1 || (cz_p->l_p==1 && cz_p->l_c>0) || cz_p->l_p<0 || cz_p->l_c<0 ) {
  printf ("CZYTAM: Liczba czytelnikow: %d, Liczba pisarzy: %d\n", cz_p->l_c, cz_p->l_p);
    printf("Blad: ....\n");
   exit(0);
  }
	else { printf ("CZYTAM: Liczba czytelnikow: %d, Liczba pisarzy: %d\n", cz_p->l_c, cz_p->l_p);
    usleep(rand()%3000000);}
    
 pthread_rwlock_unlock(&cz_p->rwlock);
}

void pisze(cz_t* cz_p){
cz_p->l_c--;

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
  //printf("\t\t\t\t\tpisze:   l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p); 
// sprawdzenie warunku poprawności i ewentualny exit
  if( cz_p->l_p>1 || (cz_p->l_p==1 && cz_p->l_c>0) || cz_p->l_p<0 || cz_p->l_c<0 ) {
  printf ("PISZE :Liczba czytelnikow: %d, Liczba pisarzy: %d\n", cz_p->l_c, cz_p->l_p);
    printf("Blad: ....\n");
    exit(0);
  }
else { printf ("PISZE :Liczba czytelnikow: %d, Liczba pisarzy: %d\n", cz_p->l_c, cz_p->l_p);
    usleep(rand()%3000000);}
    
    
}


