# $Id: Makefile,v 1.1.1.1 2006-01-02 14:22:57 quentin Exp $
CFLAGS=-Wall

all: md5.o main.c md5.h
	$(CC) $(CFLAGS) md5.o main.c -o md5sum

md5.o: md5.h

clean:
	-$(RM) md5.o md5sum
