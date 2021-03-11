CC = gcc
CFLAGS = -Wall -Werror
LFLAGS = -lm
CONSTANTS = "Constants.h"
PKG = $(shell pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 --libs --cflags)

.PHONY: clean purge

all: Redshift

Chunks.o: src/Chunks.c src/Chunks.h
		$(CC) -c src/Chunks.c $(PKG) $(CFLAGS) $(LFLAGS)

Physics.o: src/Physics.c src/Physics.h
		$(CC) -c src/Physics.c $(PKG) $(CFLAGS) $(LFLAGS)

Entities.o: src/Entities.c src/Entities.h
		$(CC) -c src/Entities.c $(PKG) $(CFLAGS) $(LFLAGS)

Menus.o: src/Menus.c src/Menus.h
		$(CC) -c src/Menus.c $(PKG) $(CFLAGS) $(LFLAGS)

Redshift.o: src/Redshift.c
		$(CC) -c src/Redshift.c $(PKG) $(CFLAGS) $(LFLAGS)

Redshift: src/Redshift.o src/Chunks.o src/Physics.o src/Entities.o
		$(CC) -o redshift src/Redshift.o src/Entities.o src/Chunks.o src/Physics.o src/Menus.c $(PKG) $(CFLAGS) $(LFLAGS)

clean: 
	    -rm -f src/*~ src/*.o

purge: clean
		-rm redshift
