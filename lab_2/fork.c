#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include"pomiar_czasu.h"

int zmienna_globalna=0;

int main(){
  
  int pid, wynik, i;

  //inicjuj_czas();
  
  //for(i=0;i<1000;i++){
    
    pid = fork(); //zwraca indentyfikator procesu potomnego 			
    
    if(pid==0){ 			
      
      zmienna_globalna++;


    char *args[4];
    args[0] = "./zajecia_2"; 
    args[1] = "Katarzyna";  
    args[2] = "Madej";    
    args[3] = NULL;        

   
    int wynik = execv(args[0], args);  
       if(wynik==-1) 
          printf("Proces potomny nie wykonal programu\n"); 
          
      exit(0);
      
    } else {					
      
      wait(NULL);
      
    }
    
  //}

 // drukuj_czas();
  
}

  
