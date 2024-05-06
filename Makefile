CC = gcc
CFLAGS = -Wall -Wextra -Werror -ansi -pedantic
VALFLAGS = --track-origins=yes --leak-check=full \
					 --show-leak-kinds=all --trace-children=yes
FILE ?= htable
ARG ?= twonodes

all: htable

val:
	valgrind ${VALFLAGS} ./${FILE} ${ARG}

hencode: hencode.o huffman.o
	${CC} hencode.o huffman.o -o hencode

htable: htable.o huffman.o
	${CC} htable.o huffman.o -o htable

hencode.o: hencode.c hencode.h
	${CC} -c -g ${CFLAGS} hencode.c

htable.o: htable.c
	${CC} -c -g htable.c

huffman.o: huffman.c huffman.h
	${CC} -c -g ${CFLAGS} huffman.c

clean:
	rm -f hencode hencode.o huffman.o



