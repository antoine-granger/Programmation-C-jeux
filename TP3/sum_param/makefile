CC=gcc
CFLAGS=-W -Wall -pedantic -ansi
LDFLAGS= -lMLV
EXEC=sum.exe
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

sum.exe: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

#main.o: grid.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

