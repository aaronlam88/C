#Makefile for UDP and TCP DAYTIME and TIME client

#================== Source Files ==================
CONNECT_SRC 	= src/errexit.c src/connectsock.c src/passivesock.c src/passiveTCP.c
UDP_DAYTIME_SRC = src/connectUDP.c src/UDPdaytime.c
TCP_TIME_SRC 	= src/connectTCP.c src/TCPtime.c
TCP_SER_SRC		= src/TCPwcServer.c
TCP_ClI_SRC		= src/TCPwcClient.c

#==================================================

#================== Object Files ==================
CONNECT_OBJ 	= obj/errexit.o obj/connectsock.o obj/passivesock.o obj/passiveTCP.o
UDP_DAYTIME_OBJ = obj/connectUDP.o obj/UDPdaytime.o
TCP_TIME_OBJ	= obj/connectTCP.o obj/TCPtime.o
TCP_SER_OBJ		= obj/TCPwcServer.o
TCP_ClI_OBJ		= obj/TCPwcClient.o
#==================================================

#================ Executable Files ================
PROGRAMS = UDPdaytime TCPtime TCPwcServer TCPwcClient
#==================================================

all: $(PROGRAMS)

obj/errexit.o: src/errexit.c
	gcc -c src/errexit.c -o obj/errexit.o

obj/connectsock.o: src/connectsock.c
	gcc -c src/connectsock.c -o obj/connectsock.o

obj/connectTCP.o: src/connectTCP.c
	gcc -c src/connectTCP.c -o obj/connectTCP.o

obj/connectUDP.o: src/connectUDP.c
	gcc -c src/connectUDP.c -o obj/connectUDP.o

obj/passivesock.o: src/passivesock.c
	gcc -c src/passivesock.c -o obj/passivesock.o

obj/passiveTCP.o: src/passiveTCP.c
	gcc -c src/passiveTCP.c -o obj/passiveTCP.o

obj/UDPdaytime.o: src/UDPdaytime.c
	gcc -c src/UDPdaytime.c -o obj/UDPdaytime.o

obj/TCPtime.o: src/TCPtime.c
	gcc -c src/TCPtime.c -o obj/TCPtime.o

obj/TCPwcServer.o: src/TCPwcServer.c
	gcc -c src/TCPwcServer.c -o obj/TCPwcServer.o

obj/TCPwcClient.o: src/TCPwcClient.c
	gcc -c src/TCPwcClient.c -o obj/TCPwcClient.o

UDPdaytime: $(CONNECT_OBJ) $(UDP_DAYTIME_OBJ)
	gcc $(CONNECT_OBJ) $(UDP_DAYTIME_OBJ) -o UDPdaytime

TCPtime: $(CONNECT_OBJ) $(TCP_TIME_OBJ)
	gcc $(CONNECT_OBJ) $(TCP_TIME_OBJ) -o TCPtime

TCPwcServer: $(CONNECT_OBJ) $(TCP_SER_OBJ)
	gcc $(CONNECT_OBJ) $(TCP_SER_OBJ) -o TCPwcServer

TCPwcClient: $(CONNECT_OBJ) $(TCP_ClI_OBJ) obj/connectTCP.o
	gcc $(CONNECT_OBJ) $(TCP_ClI_OBJ) obj/connectTCP.o -o TCPwcClient

clean:
	rm -f obj/*.o $(PROGRAMS)