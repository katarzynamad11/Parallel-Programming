#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

int zmienna_wspolna=0;

#define WYMIAR 1000
#define ROZMIAR WYMIAR*WYMIAR
double a[ROZMIAR],b[ROZMIAR],c[ROZMIAR];


double czasozajmowacz(){
  int i, j, k;
  int n=WYMIAR;
  for(i=0;i<ROZMIAR;i++) a[i]=1.0*i;
  for(i=0;i<ROZMIAR;i++) b[i]=1.0*(ROZMIAR-i);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      c[i+n*j]=0.0;
      for(k=0;k<n;k++){
	c[i+n*j] += a[i+n*k]*b[k+n*j];
      }
    }
  }
  return(c[ROZMIAR-1]);
}

void * zadanie_watku (void * arg_wsk)
{
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	printf("\twatek potomny: uniemozliwione zabicie\n");

	czasozajmowacz();

	printf("\twatek potomny: umozliwienie zabicia\n");
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

	pthread_testcancel();

	zmienna_wspolna++;
	printf("\twatek potomny: zmiana wartosci zmiennej wspolnej\n");

	return(NULL);
}

int main()
{
	pthread_t tid;
	pthread_attr_t attr;
	void *wynik;
	int i;

	//--------------------------------Wątek przyłączalny----------------------------------------------
	
	printf("watek glowny: tworzenie watku potomnego nr 1\n");

	/*Tu wstaw kod tworzenia wątku z domyślnymi własnościami*/
	pthread_create(&tid, NULL, zadanie_watku, NULL); 
	
	sleep(2); // czas na uruchomienie watku, czeka 2 sekundy

	printf("\twatek glowny: wyslanie sygnalu zabicia watku\n");
	pthread_cancel(tid); // wysyla sygnal anulowania 

	//Co nalezy zrobić przed sprawdzeniem czy wątki się skonczyły?
	
	pthread_join(tid, &wynik); //oczekujemy na zakonczenie pracy watku
	
	if (wynik == PTHREAD_CANCELED) //sprawdza wartosc wskaznika, jesli jest ona rowna to watek potomny zostal anulowany 
		printf("\twatek glowny: watek potomny zostal zabity\n");
	else
		printf("\twatek glowny: watek potomny NIE zostal zabity - blad\n");

	//---------------------------------Odłączanie wątku-------------------------------------------------

	zmienna_wspolna = 0; // wartosc zmieniana przez watek potomny bezposrednio przed zakonczeniem pracy

	printf("watek glowny: tworzenie watku potomnego nr 2\n");

	/*Tu wstaw kod tworzenia wątku z domyślnymi własnościami*/
	pthread_create(&tid, NULL, zadanie_watku, NULL);

	sleep(2); // czas na uruchomienie watku

	printf("\twatek glowny: odlaczenie watku potomnego\n");
	//Instrukcja odłączenia?
	pthread_detach(tid); //watek traci mozliwosc prostej sunchronizacji z watkiem potomnym
	
	printf("\twatek glowny: wyslanie sygnalu zabicia watku odlaczonego\n");
	pthread_cancel(tid);
     
	//Czy watek został zabity? Jak to sprawdzić?
	// Po drzemce wątek postanawia przyjmować sygnały anulowania i od razu sprawdza czy jakies nie pojawily się
	
	for(i=0; i<10; i++) {
	sleep(1); //punkt anulowania
	if(zmienna_wspolna!=0) break;
	}
	
	if(zmienna_wspolna==0) //zmienil wartosc, to najprawdobobniej zostal zabity 
	printf("\twatek glowny: odlaczony watek potomny prawdopodobnie zostal zabity\n");
	else
	printf("\twatek glowny: odlaczony watek potomny prawdopodobnie nie zostal zabity\n");
	
	
	
	//-------------------------------------Wątek odłączony-------------------------------------------------
	
	//Inicjacja atrybutów?
	// wczesniej byla zainicjowana 
	size_t rozmiar
	pthread_attr_init(&attr);
	
	//Ustawianie typu watku na odłaczony
	pthread_attr_getstacksize(&attr, &rozmiar);
	
	printf("watek glowny: tworzenie odlaczonego watku potomnego nr 3\n");
	pthread_create(&tid, &attr, zadanie_watku, NULL);

	//Niszczenie atrybutów
	pthread_attr_destroy(&attr); // w celu odzyskania zasobow
	
	printf("\twatek glowny: koniec pracy, watek odlaczony pracuje dalej\n");
	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
	//exit(0);
	/*
	pthread_exit(NULL) - kiedy watek glowny go wywola, wszystkie pozstale  dzialajace watki nadal beda mogly
	kontynuowac do momentu az zakoncza prace
	exit(0) - natychmiast konczy dzialanie programu, wszystkie dzialajace watki natychmiast umieraja
	*/
}


