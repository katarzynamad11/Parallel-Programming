# kompilator c
#CCOMP = /usr/lib64/openmpi/bin/mpicc
CCOMP = /usr/bin/mpicc

# konsolidator
LOADER = $(CCOMP)

#MPIRUN = /usr/lib64/openmpi/bin/mpiexec --oversubscribe
#MPIRUN = /usr/bin/mpiexec -display-map --bind-to core --map-by core 
#MPIRUN = /usr/bin/mpiexec -display-map --bind-to core --map-by socket 
MPIRUN = /usr/bin/mpiexec -display-map --bind-to core:overload-allowed --map-by socket --oversubscribe 

# opcje optymalizacji:
# wersja do debugowania
# OPT = -g -DDEBUG -p
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3 -fopenmp -p
OPT = -O3
#OPT = -O0 

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lpomiar_czasu
LIB =  -lm
#LIB = -L/opt/intel//mkl/8.1/lib/em64t -lmkl_em64t
#LIB = -L/opt/intel//mkl/8.1/lib/32 -lmkl_ia32
#LIB = -L/opt/intel/mkl/10.1.0.015/lib/em64t/ -lmkl -liomp5 -lpthread

# zaleznosci i komendy
all: mat_vec_row_MPI run

#mat_vec_row_MPI: mat_vec_row_MPI.o mat_vec.o pomiar_czasu.o
#	$(LOADER) $(OPT) mat_vec_row_MPI.o mat_vec.o pomiar_czasu.o -o mat_vec_row_MPI $(LIB)
mat_vec_row_MPI: mat_vec_row_MPI.o
	$(LOADER) $(OPT) mat_vec_row_MPI.o -o mat_vec_row_MPI $(LIB)

#mat_vec_row_MPI.o: mat_vec_row_MPI.c pomiar_czasu.h
mat_vec_row_MPI.o: mat_vec_row_MPI.c
	$(CCOMP) -c $(OPT) mat_vec_row_MPI.c $(INC)

#mat_vec.o: mat_vec.c
#	$(CCOMP) -c $(OPT) mat_vec.c

#pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
#	$(CCOMP) -c $(OPT) pomiar_czasu.c

run:
	$(MPIRUN) --oversubscribe -np 8  ./mat_vec_row_MPI

clean:
	rm -f *.o ./mat_vec_row_MPI
