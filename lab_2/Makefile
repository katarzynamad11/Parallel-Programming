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
INC = -I../pomiar_czasu

# biblioteki
LIB = -L../pomiar_czasu -lpomiar_czasu -lm

# zaleznosci i komendy
fork: fork.o 
	$(LOADER) $(OPT) fork.o -o fork $(LIB)

# jak uzyskac plik fork.o ?
fork.o: fork.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) fork.c $(INC) 

# zaleznosci i komendy
clone: clone.o 
	$(LOADER) $(OPT) clone.o -o clone $(LIB)

# jak uzyskac plik clone.o ?
clone.o: clone.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) clone.c $(INC) 

# zaleznosci i komendy
new_clone: new_clone.o 
	$(LOADER) $(OPT) new_clone.o -o new_clone $(LIB)

# jak uzyskac plik clone.o ?
new_clone.o: new_clone.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) new_clone.c $(INC) 
	
flagi_clone: flagi_clone.o 
	$(LOADER) $(OPT) flagi_clone.o -o flagi_clone $(LIB)

# jak uzyskac plik clone.o ?
flagi_clone.o: new_clone.c 
	$(CCOMP) -c $(OPT) flagi_clone.c $(INC) 	


clean:
	rm -f *.o fork clone
