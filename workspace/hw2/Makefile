# Make file
# all source code should be in src folder
# all objects will be place in obj folder
# link necessary objects to create exe program

#================== Source Files ==================
ERREXIT_SRC = src/errexit.c 
SERVERS_SRC = src/passivesock.c src/udpiServer.c src/udpTPRServer.c
CLIENTS_SRC = src/connectsock.c src/udpFileClient.c
#==================================================

#================== Object Files ==================
SERVER_OBJ = obj/errexit.o obj/passivesock.o
CLIENT_OBJ = obj/errexit.o obj/connectsock.o
UDP_OBJ    = obj/udpFileServer.o
TCP_OBJ    = obj/tcpFileServer.o
#==================================================

#================ Executable Files ================
UDP = udpFileClient udpiServer udpTPRServer udpPTServer udpPPRServer udpPFServer
TCP = tcpFileClient tcpiServer tcpTPRServer tcpPTServer tcpPPRServer tcpPFServer
PROGRAM = $(UDP) $(TCP)
#==================================================

all: $(PROGRAM)

udp: $(UDP)

tcp: $(TCP)

obj/%.o: src/%.c
	@gcc -Wall -c $< -o $@

udpFileClient: obj/udpFileClient.o $(CLIENT_OBJ)
	gcc -Wall -o udpFileClient obj/udpFileClient.o $(CLIENT_OBJ)

udpiServer: obj/udpiServer.o $(SERVER_OBJ) $(UDP_OBJ)
	gcc -Wall -o udpiServer obj/udpiServer.o $(SERVER_OBJ) $(UDP_OBJ)

udpTPRServer: obj/udpTPRServer.o $(SERVER_OBJ) $(UDP_OBJ)
	gcc -Wall -pthread -o udpTPRServer obj/udpTPRServer.o $(SERVER_OBJ) $(UDP_OBJ)

udpPTServer: obj/udpPTServer.o $(SERVER_OBJ) $(UDP_OBJ)
	gcc -Wall -pthread -o udpPTServer obj/udpPTServer.o $(SERVER_OBJ) $(UDP_OBJ)

udpPPRServer: obj/udpPPRServer.o $(SERVER_OBJ) $(UDP_OBJ)
	gcc -Wall -o udpPPRServer obj/udpPPRServer.o $(SERVER_OBJ) $(UDP_OBJ)

udpPFServer: obj/udpPFServer.o $(SERVER_OBJ) $(UDP_OBJ)
	gcc -Wall -o udpPFServer obj/udpPFServer.o $(SERVER_OBJ) $(UDP_OBJ)

tcpFileClient: obj/tcpFileClient.o $(CLIENT_OBJ)
	gcc -Wall -o tcpFileClient obj/tcpFileClient.o $(CLIENT_OBJ)

tcpiServer: obj/tcpiServer.o $(SERVER_OBJ) $(TCP_OBJ)
	gcc -Wall -o tcpiServer obj/tcpiServer.o $(SERVER_OBJ) $(TCP_OBJ)

tcpTPRServer: obj/tcpTPRServer.o $(SERVER_OBJ) $(TCP_OBJ)
	gcc -Wall -pthread -o tcpTPRServer obj/tcpTPRServer.o $(SERVER_OBJ) $(TCP_OBJ)

tcpPTServer: obj/tcpPTServer.o $(SERVER_OBJ) $(TCP_OBJ)
	gcc -Wall -pthread -o tcpPTServer obj/tcpPTServer.o $(SERVER_OBJ) $(TCP_OBJ)

tcpPPRServer: obj/tcpPPRServer.o $(SERVER_OBJ) $(TCP_OBJ)
	gcc -Wall -o tcpPPRServer obj/tcpPPRServer.o $(SERVER_OBJ) $(TCP_OBJ)

tcpPFServer: obj/tcpPFServer.o $(SERVER_OBJ) $(TCP_OBJ)
	gcc -Wall -o tcpPFServer obj/tcpPFServer.o $(SERVER_OBJ) $(TCP_OBJ)

clean:
	@rm -v obj/*.o $(PROGRAM)