CC=gcc
CFLAGS=-W -Wall -pedantic -ansi
LDFLAGS= -lMLV
EXEC=read_file
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

read_file: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)