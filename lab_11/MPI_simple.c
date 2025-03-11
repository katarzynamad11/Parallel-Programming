#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h> // dla funkcji gethostname

#define HOSTNAME_LEN 128

int main(int argc, char** argv) { 
  
  int rank, ranksent, size, source, dest, tag, i; 
  char hostname[HOSTNAME_LEN] = {0}; //tablica przechowujaca wysylana nazwe hosta
  char hostname_received[HOSTNAME_LEN] = {0}; //tablica przechowujaca odebrana nazwe hosta
  MPI_Status status; //przechowuje informacje na temat wysylanych danych 
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // pobranie nazwy hosta 
  gethostname(hostname, sizeof(hostname));
  
  if (size > 1) {
    if (rank != 0) { 
      dest = 0; // identyfikator procesu 
      tag = 0;  // oznaczenie komunikatora 

      // wysłanie rangi do procesu 
      MPI_Send(&rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);

      // wysłanie nazwy hosta do procesu 
      MPI_Send(hostname, HOSTNAME_LEN, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
      
    } else {
      for (i = 1; i < size; i++) { 
        // odbieranie rangi
        MPI_Recv(&ranksent, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        // odbieranie nazwy hosta
        MPI_Recv(hostname_received, HOSTNAME_LEN, MPI_CHAR, status.MPI_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

       
        printf("Dane od procesu o randze %d: adres hosta = %s (i = %d)\n", 
               status.MPI_SOURCE,  hostname_received, i);
      }
    }
  } else {
    printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  MPI_Finalize(); 
  
  return 0;
}

