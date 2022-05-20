CC=gcc
CFLAGS=-W -Wall -pedantic -ansi
LDFLAGS= -lMLV
EXEC=write_in_file
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

write_in_file: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)