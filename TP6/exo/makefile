CC=gcc
CFLAGS=-W -Wall -pedantic -ansi -g
LDFLAGS= -lMLV
EXEC=exo
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

exo: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)