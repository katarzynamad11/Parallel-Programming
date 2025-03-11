# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3

# pliki naglowkowe
INC = -I../pomiar_czasu #pliki nagłówkowe znajdują się w katalogu pomiar_czasu

# biblioteki
LIB = -L../pomiar_czasu -lm #określa gdzie znajdują się biblioteki do linkowania. lm - program będzie używał biblioteki matematycznej

# zaleznosci i komendy
moj_program: moj_program.o 
	$(LOADER) $(OPT) moj_program.o -o moj_program $(LIB) -l pomiar_czasu

# jak uzyskac plik moj_program.o ?
moj_program.o: moj_program.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) $(INC) moj_program.c  
	


#pomiar_czasu.o: pomiar_czasu.c pomiar_czasu.h
#	$(CCOMP) -c $(OPT) pomiar_czasu.c

clean:
	rm -f *.o
