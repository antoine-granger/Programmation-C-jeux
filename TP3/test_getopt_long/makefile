CC=gcc
CFLAGS= -pedantic -ansi
LDFLAGS= -lMLV
EXEC=get_otp_long.exe
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

get_otp_long.exe: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)

