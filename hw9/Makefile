# Note, you must change the port to your unique port number (between 1000 and 2^16-1) based on your Student ID
PORT = 29177
PROGRAMS = server client server_tpr server_tp server_lf
S = -std=c99 -ggdb

both: $(PROGRAMS)

server: server.c server_threadPerRequest.c server_threadPool.c
	gcc $S server.c -o server
	gcc $S server_threadPerRequest.c -lpthread -o server_tpr
	gcc $S server_threadPool.c -lpthread -o server_tp
	gcc $S server_leaderFollower.c -lpthread -o server_lf

client: client.c
	gcc $S client.c -lpthread Timer.c -o client

test: both
	server $(PORT) &
	echo Starting client
	client `hostname` $(PORT)
	ls -lr Thread_*
	du

clean:
	/bin/rm -rf $(PROGRAMS) Thread_*
