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


	
pub_sym_1: pub_sym_1.o 
	$(LOADER) $(OPT) pub_sym_1.o -o pub_sym_1 $(LIB)

pub_sym_1.o: pub_sym_1.c 
	$(CCOMP) -c $(OPT) pub_sym_1.c $(INC) 

pub_sym_2: pub_sym_2.o 
	$(LOADER) $(OPT) pub_sym_2.o -o pub_sym_2 $(LIB)

pub_sym_2.o: pub_sym_2.c 
	$(CCOMP) -c $(OPT) pub_sym_2.c $(INC) 
	
	
pub_sym_1.2: pub_sym_1.2.o 
	$(LOADER) $(OPT) pub_sym_1.2.o -o pub_sym_1.2 $(LIB)

pub_sym_1.2.o: pub_sym_1.2.c 
	$(CCOMP) -c $(OPT) pub_sym_1.2.c $(INC) 


clean:
	rm -f *.o 
