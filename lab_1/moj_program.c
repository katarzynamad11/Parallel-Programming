#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "pomiar_czasu.h" // dołączenie pliku nagłówkowego (7a)
const int liczba = 1000;

main(){

  double a, b, c, t1, t2;
  int i,j,k,l;

  k = -50000;
  //start - lepiej przed,  ale nie ma takiego dużego znaczenia
  

  inicjuj_czas(); //wywołanie funkcji (7b)
 
  
  for(i=0;i<liczba;i++){

    printf("%d ",k+i);

  }
  printf("\n");

  printf("Czas wykonania %d operacji wejscia/wyjscia: \n",liczba);
 
  drukuj_czas(); // wywołanie funkcji (7b)
  
  a = 1.000001;
  //start - przy arytmetycznych ma znaczenie czy przed printf, czy po
  
  printf("Wynik operacji arytmetycznych: %lf\n", a);
  printf("Czas wykonania %d operacji arytmetycznych: \n",liczba);
 
  t1=czas_zegara(); //(7c)
  t2=czas_CPU(); //(7c)

  for(i=0;i<liczba;i++){

    a = 1.000001*a+0.000001; 

  }
  
  t1= czas_zegara()-t1;//(7c)
  t2=czas_CPU()-t2;//(7c)

  //koniec
  
  printf("Czas zegara: %lf\n", t1);
  printf("Czas CPU: %lf\n", t2);
 
}
