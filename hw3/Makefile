# Makefile: PhotoLab

DEBUG = -g -DDEBUG
CFLAG = -Wall -ansi $(DEBUG) -c
DFLAG = -Wall -ansi -c

all: PhotoLab

PhotoLab: FileIO.o Advanced.o DIPs.o PhotoLab.o
	gcc -Wall -ansi -std=c99 FileIO.o Advanced.o DIPs.o PhotoLab.o -o PhotoLab

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -Wall -ansi -std=c99 -c FileIO.c -o FileIO.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc -Wall -ansi -std=c99 -c Advanced.c -o Advanced.o 

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -Wall -ansi -std=c99 -c DIPs.c -o DIPs.o

PhotoLabTest: PhotoLab.c Constants.h Advanced.h DIPs.h FileIO.h
	gcc -Wall -ansi -std=c99 -c PhotoLab.c -o PhotoLabTest

clean:
	rm -rf *o PhotoLab 
