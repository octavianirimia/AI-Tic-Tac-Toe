# This makefile is intended for macs with apple silicon
# and SDL installed via homebrew


CC = clang

CFLAGS = $(shell sdl2-config --cflags)

LDFLAGS = $(shell sdl2-config --libs)

all: program

program: main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o program main.c graphics.c logic.c

run: clean program
	./program

clean:
	rm -f program