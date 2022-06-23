CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=-lMLV
LDLIBS=
EXEC=clear snake clean
SRC= $(wildcard src/*.c)
SRCO= $(shell find . -name *.o)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

snake: $(OBJ)
    $(CC) -o bin/$@ $^ $(LDFLAGS)
    mv src/*.o bin/

%.o: %.c
    $(CC) -o $@ -c $< $(CFLAGS)

game.o: game.h
snake.o: snake.h

.PHONY: clean clear tgz

clean:
    rm -rf $(SRCO)

clear:
    rm -rf bin/*

tgz:
    tar czf ../GRANGER_Antoine_Snake2022.tgz *
