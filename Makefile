CC=gcc
CXX=g++
NAME=mem
CFLAGS=-Wall -ggdb
LDFLAGS=

all : $(NAME)

$(NAME).o : $(NAME).c
	$(CC) -c $(CFLAGS) -o $@ $<

$(NAME) : $(NAME).o
	$(CC) -o $@ $^ ${LDFLAGS}

memtest : $(NAME)
	valgrind -v --show-reachable=yes --leak-check=full ./$^

clean :
	-rm -f $(NAME) *.o

