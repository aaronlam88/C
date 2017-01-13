#####################################################
# 01/28/2016 Aaron Lam
# Makefile: Makefile for HW3 class ICS53
#####################################################

CC = gcc
LFLAGS = -Wall -ggdb
CFLAGS = -Wall -c 

OBJECTS = main.o my_ls.o
SOURCES = main.c my_ls.c
HEADERS = my_ls.h
RUNABLE = my_ls


all: my_ls

main.o: main.c 
	$(CC) $(CFLAGS) main.c -o main.o

my_ls.o:  my_ls.h my_ls.c
	$(CC) $(CFLAGS) my_ls.c -o my_ls.o

my_ls: main.o my_ls.o
	$(CC) $(LFLAGS) $(OBJECTS) -o my_ls


clean:
	rm $(OBJECTS) $(RUNABLE)