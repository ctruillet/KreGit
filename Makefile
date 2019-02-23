GCC=gcc
LDFLAGS=-lm
LIB=./lib
INCLUDE=./include
CFLAGS=-Wall -g
SRC=./src/main.c ./src/Complexe.c
OBJ=$(SRC:.c=.o)
EXEC=out

all:$(EXEC)

$(EXEC): $(OBJ) $(INCLUDE)/*.h
	$(GCC) $(CFLAGS) -o $(EXEC) $(OBJ) -I$(INCLUDE) $(LDFLAGS)
	mv src/*.o lib

main.o: main.c 
	$(GCC) $(CFLAGS) -o main.o -c ./src/main.c $(LDFLAGS)
	
Complexe.o: Complexe.c $(INCLUDE)/Complexe.h
	$(GCC) $(CFLAGS) -o Complexe.o -c ./src/Complexe.c $(LDFLAGS)
	
clean:
	rm $(EXEC)
	rm lib/*.o