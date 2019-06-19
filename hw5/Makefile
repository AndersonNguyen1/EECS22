#######################################################################
# Homework Assignment 5, for EECS 22, Fall 2017
#
# Author: Tim Schmidt
# Date: 11/09/2017
#
# Makefile: Makefile for HW 5
#
######################################################################:
all: MovieLab
	
FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -Wall -ansi -std=c99 -c FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -Wall -ansi -std=c99 -c DIPs.c -o DIPs.o

Image.o: Image.c Image.h Constants.h
	gcc -Wall -ansi -std=c99 -c Image.c -o Image.o

ImageList.o: ImageList.c ImageList.h Constants.h
	gcc -Wall -ansi -std=c99 -c ImageList.c -o ImageList.o

Movie.o: Movie.c Movie.h Constants.h
	gcc -Wall -ansi -std=c99 -c Movie.c -o Movie.o

MovieLab: FileIO.o DIPs.o Image.o ImageList.o Movie.o MovieLab.o
	gcc -Wall -ansi -std=c99 FileIO.o DIPs.o Image.o ImageList.o Movie.o MovieLab.o -o MovieLab
 
clean:
	rm -rf *o MovieLab
