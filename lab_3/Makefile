# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
 #OPT = -O3

# pliki naglowkowe
INC = -I/usr/include

# biblioteki
LIB = -L/usr/lib64 -lpthread -lm


watki: pthreads_detach_kill.o 
	$(LOADER) $(OPT) pthreads_detach_kill.o -o watki $(LIB)

pthreads_detach_kill.o: pthreads_detach_kill.c 
	$(CCOMP) -c $(OPT) pthreads_detach_kill.c $(INC) 
	
zad_2: zad_2.o 
	$(LOADER) $(OPT) zad_2.o -o zad_2 $(LIB)

zad_2.o: zad_2.c 
	$(CCOMP) -c $(OPT) zad_2.c $(INC) 

zad_3: zad_3.o 
	$(LOADER) $(OPT) zad_3.o -o zad_3 $(LIB)

zad_3.o: zad_3.c 
	$(CCOMP) -c $(OPT) zad_3.c $(INC) 
	
atrybuty: atrybuty.o 
	$(LOADER) $(OPT) atrybuty.o -o atrybuty $(LIB)

atrybuty.o: zad_3.c 
	$(CCOMP) -c $(OPT) atrybuty.c $(INC) 

clean:
	rm -f *.o 
