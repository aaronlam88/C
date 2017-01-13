#####################################################
# 02/08/16 Aaron Lam
# Makefile: Makefile for HW5 ICS53 Winter2015
# 02/08/16 Aaron Lam: initial solution version
#####################################################
CC     = gcc
DEBUG  = -ggdb -g -DDEBUG
#CFLAGS = -ansi -Wall -c
LFLAGS = -Wall

# design names
DESIGN = handle_signals my_shell
#OBJS = handle_signals.o my_shell.o
SRCS = handle_signals.c my_shell.c

all: handle_signals my_shell
	@echo "make finished!"

handle_signals: handle_signals.c
	$(CC) $(LFLAGS) handle_signals.c -o handle_signals

my_shell: my_shell.c
	$(CC) $(LFLAGS) my_shell.c -o my_shell

#target to clean the directory
clean:
	rm -f $(DESIGN)
	@echo removed: $(DESIGN)
