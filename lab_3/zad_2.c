#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

/* Implementacja nowego programu (np.pthreads_zadanie2.c) w którym do N wątków przesyłane są indywidualne identyfikatory (sprawdzenie wyniku na iteratorze pętli i dedykowanej tablicy) */


//przesylanie swojego identyfikatora i systemowego (pthread_self())
void * watek(void * arg_wsk) {
	int id;
	id = *((int*)arg_wsk);
	
	pthread_t system_id = pthread_self();
	printf ("[id = %d]\t	   [system_id = %li]\n", id, system_id);
	return ((void*)0);
}


int main() {

	int THREADS_NUMBER = 10;
	int moj_id[THREADS_NUMBER];
	pthread_t system_thread_id[THREADS_NUMBER];
		
	for (int i =0; i <THREADS_NUMBER; i++)
	{
		moj_id[i] = i;
	}
	
	for (int i = 0; i< THREADS_NUMBER;i++)
	{
		pthread_create(&system_thread_id[i], NULL, watek, &i); 
	} 
	
	for (int i=0; i <THREADS_NUMBER; i++)
	{
		//zakonczenie po wykonaniu watku
		int check = pthread_join(system_thread_id[i], NULL);
		if(check == 0){
			printf("\tWatek glowny: watek potomny sie skonczyl %i\n\n", i);
		}
		else {
			printf("\tWatek glowny: watek potomny nadal trwa %i\n\n", i);
		}
	}
	return 0;
	
}


