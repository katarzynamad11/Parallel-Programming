#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>

#define ILE_MUSZE_WYPIC 333  // Zwiększona liczba powtórzeń

void *watek_klient(void *arg);
int liczba_kufli; // dodanie zmiennej globalnej
pthread_mutex_t mutex, mutex2; // deklaruje dwa obiekty, pthread_mutex_t - sluży do definiowania muteksów, które są używane do synchronizacji wątków


int main(void) {
    pthread_t *tab_klient; // deklaruje wskaźnik tab_klient typu pthread_t
    int *tab_klient_id;// bedzie uzywany do przechowywania tablicy identyfikatorow klientow

    int l_kl, l_kf, l_kr, i;
    
    // inicjalizacja mutexow z domyslnymi parametrami
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex2, NULL);
    
    
    int poczatkowa_liczba_kufli;

    printf("\nLiczba klientow: "); 
    scanf("%d", &l_kl);

    printf("\nLiczba kufli: "); 
    scanf("%d", &l_kf);
    
    poczatkowa_liczba_kufli = l_kf;
    liczba_kufli = l_kf;

    l_kr = 1000000000;  // Niezmienna liczba kranów

    tab_klient = (pthread_t *)malloc(l_kl * sizeof(pthread_t));
    tab_klient_id = (int *)malloc(l_kl * sizeof(int));
    for (i = 0; i < l_kl; i++) 
        tab_klient_id[i] = i;

    printf("\nOtwieramy pub (simple)!\n");
    printf("\nLiczba wolnych kufli %d\n", l_kf);

    for (i = 0; i < l_kl; i++) {
        pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]);
    }
    for (i = 0; i < l_kl; i++) {
        pthread_join(tab_klient[i], NULL);
    }

	// sprawdzenie czy poczatkowa liczba kufli sie zmienila 
    if (poczatkowa_liczba_kufli == liczba_kufli) {
        printf("\nLiczba kufli w pubie pozostała niezmieniona: %d\n", liczba_kufli);
    } else {
        printf("\nBłąd! liczba kufli zmieniła się z %d na %d\n", poczatkowa_liczba_kufli, liczba_kufli);
    }

    printf("\nZamykamy pub!\n");

    free(tab_klient);
    free(tab_klient_id);

    return 0;
}

void *watek_klient(void *arg_wsk) {
    int moj_id = *((int *)arg_wsk);
    int i;

    printf("\nKlient %d, wchodzę do pubu\n", moj_id);

    for (i = 0; i < ILE_MUSZE_WYPIC; i++) {
    	
    	
    
    	pthread_mutex_lock(&mutex); // zamykanie zamku
    	
    	
        printf("\nKlient %d, wybieram kufel\n", moj_id);
        liczba_kufli--;
        usleep(1);
         if (liczba_kufli < 0) {
            printf("\nBłąd! Liczba kufli jest ujemna !!!");
            return NULL;
            }
  	pthread_mutex_unlock(&mutex); // otwieram zamek
        
	printf ("\nAktualna liczba kufli: %d\n", liczba_kufli);
	int j=0;
	pthread_mutex_lock(&mutex2);
         printf("\nKlient %d, nalewam z kranu %d\n", moj_id, j); 
         j++;
         pthread_mutex_unlock(&mutex2);
    usleep(30);
    
    printf("\nKlient %d, pije\n", moj_id); 
    nanosleep((struct timespec[]){{0, 50000000L}}, NULL);
  	pthread_mutex_lock(&mutex); //zamykam zamek 
        printf("\nKlient %d, odkładam kufel\n", moj_id);
         liczba_kufli++; 
        pthread_mutex_unlock(&mutex); //otwieram zamek
    }

    printf("\nKlient %d, wychodzę z pubu\n", moj_id);

    return NULL;
}

