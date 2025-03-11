#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h> 
#include <stdbool.h> 

#define HOSTNAME_LEN 128
#define ROUNDS 5 // Liczba rund komunikacji

int main(int argc, char** argv) { 
  int rank, ranksent, size, source, dest, tag = 0, i; 
  
  
  MPI_Status status;
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int acc = 0;
  // Topologia pierścienia - zamknięty: niekontrolowane, otwarty: kontrolowane
  int send_rank = (rank + 1 == size) ? 0 : rank + 1;
  int recv_rank = (rank - 1 < 0) ? size - 1 : rank - 1;
  bool break_loop = true; // true to otwarty, false to zamknięty

  if (rank == 0) { // Jeśli proces 0, to wysyłaj, potem odbieraj
    
    for (i = 0; i < ROUNDS; i++) {
    acc+=1;
        MPI_Send(&acc, 1, MPI_INT, send_rank, tag, MPI_COMM_WORLD);
        printf("Proces %d: wysłał liczbę %d do procesu %d\n", rank, acc, send_rank);
        
        if (break_loop) { break; }

        MPI_Recv(&acc, 1, MPI_INT, recv_rank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("Proces %d: odebrał liczbę %d od procesu %d\n", rank, acc, recv_rank);
    }
  } else {
    for (i = 0; i < ROUNDS; i++) {
        MPI_Recv(&acc, 1, MPI_INT, recv_rank, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("Proces %d: odebrał liczbę %d od procesu %d\n", rank, acc, recv_rank);
        acc+=1;
        if (send_rank == 0 && break_loop) { break; }

        MPI_Send(&acc, 1, MPI_INT, send_rank, tag, MPI_COMM_WORLD);
        printf("Proces %d: wysłał liczbę %d do procesu %d\n", rank, acc, send_rank);
        
        if (break_loop) { break; }
    }
  }

  MPI_Finalize(); 
  
  return 0;
}

