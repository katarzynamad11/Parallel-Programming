#include<pthread.h>
static int gthread_num = 0;
static int waiting_threads = 0;
static pthread_cond_t cond;
static pthread_mutex_t mutex;

void bariera_init(int thread_num) {
  gthread_num = thread_num;
  pthread_cond_init(&cond, 0x0); //tworzenie zmiennej warunku (zmienne warunku są zmiennymi wspólnymi dla wątków, które służą do indentikacji grupy uśpionych watków 
  pthread_mutex_init(&mutex, 0x0);
}

void bariera(void) {
pthread_mutex_lock(&mutex);
waiting_threads++;
	if(waiting_threads == gthread_num) {
	   waiting_threads = 0;
	   pthread_cond_broadcast(&cond); //rozgłaszanie sygnału - budzenie wszystkich wątków będących na zmiennej cond
	   }
	else{
	 pthread_cond_wait(&cond, &mutex); // uśpienie wątku w miejsu indentyfikowanym przez zmienną cond - wątek śpi do momentu sygnału budzenia dla zmiennej cond 
	}
	   pthread_mutex_unlock(&mutex);
}
