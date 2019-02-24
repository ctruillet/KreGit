MAKE = make
GCC = gcc
LIBFLAGS = -lm
CFLAGS = -Wall -g
INCLUDE = include/
SRC = $(wildcard src/*.c)
MOVE = mv
EXC = ./bin/kregit
LIB = lib/
GIT = git
ADD = add .
COMMIT = commit -m
PUSH = push
REBASE = rebase
READ = @read -p
BIN = bin/*
LOG = log/*

all : 
	$(MAKE) compile -s
	
compile :
	$(GCC) $(CFLAGS) -I $(INCLUDE) -c $(SRC) $(LIBFLAGS)
	$(MOVE) *.o $(LIB)
	$(GCC) $(CFLAGS) -o $(EXC) $(LIB)*.o $(LIBFLAGS)

run :
	$(EXC)

git :
	$(READ) "Enter the message to set up the commit : " message; \
        $(GIT) $(ADD) && $(GIT) $(COMMIT) "$$message";
		$(GIT) $(REBASE) && $(GIT) $(PUSH);

clean :
	rm $(BIN) $(LIB)*

log :
	rm $(LOG)