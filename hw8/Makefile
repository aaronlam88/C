CC     = gcc
DEBUG  = -ggdb -g -DDEBUG
CFLAGS = -Wall

SCR = cp_server.c cp_client.c ls_server.c ls_client.c
EXE = cp_server 	cp_client 	ls_server 	ls_client

all: $(EXE)

cp_server: cp_server.c
	$(CC) $(CFLAGS) cp_server.c -o cp_server

cp_client: cp_client.c
	$(CC) $(CFLAGS) cp_client.c -o cp_client

ls_server: ls_server.c
	$(CC) $(CFLAGS) ls_server.c -o ls_server

ls_client: ls_client.c
	$(CC) $(CFLAGS) ls_client.c -o ls_client

clean:
	rm -rf $(EXE)