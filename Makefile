MAKE = make
GCC = gcc
ECHO = echo
LIBFLAGS = -lm -lcrypt
CFLAGS = -Wall -g -ggdb
INCLUDE = include/
SRC = $(wildcard src/*.c)
MOVE = mv
EXC = ./bin/kregit
LIB = lib/
GIT = git
ADD = add .
COMMIT = commit -m
PUSH = push
REBASE = pull --rebase
READ = @read -p
BIN = bin/*
LOG = log/*

all :
	@mkdir -p bin
	@mkdir -p lib
	@mkdir -p data
	@mkdir -p log
	@mkdir -p data/account; mkdir -p data/user_account
	$(MAKE) compile -s
	$(MAKE) run -s
compile :
	@$(GCC) $(CFLAGS) -I $(INCLUDE) -c $(SRC) $(LIBFLAGS)
	@$(MOVE) *.o $(LIB)
	@$(GCC) $(CFLAGS) -o $(EXC) $(LIB)*.o $(LIBFLAGS)

run :
	@$(ECHO) '\n\n'------------------DOCUMENTATION------------------;
	@$(ECHO) '\n'La documentation est disponible dans le dossier doc/documentation en ouvrant le fichier index.html;
	@$(ECHO) '\n'----------------------KreGit---------------------;
	@$(EXC)

git :
	chmod 755 *
	$(READ) "Enter the message to set up the commit : " message; \
        $(GIT) $(ADD) && $(GIT) $(COMMIT) "$$message";
		$(GIT) $(REBASE) && $(GIT) $(PUSH);

clean :
	rm $(BIN) $(LIB)*
	$(MAKE) cleanlog

cleanlog :
	rm $(LOG)
