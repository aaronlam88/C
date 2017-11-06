# Make file
# all source code should be in src folder
# all objects will be place in obj folder
# link necessary objects to create exe program

#================== Source Files ==================
ERREXIT_SRC = src/errexit.c 
HELPER_SRC  = src/mystring.c src/Timer.c
SERVERS_SRC = src/passivesock.c
CLIENTS_SRC = src/connectsock.c
#==================================================

#================== Object Files ==================
HELPER_OBJ = obj/mystring.o obj/http_helper.o obj/Timer.o
SERVER_OBJ = obj/errexit.o obj/passivesock.o
CLIENT_OBJ = obj/errexit.o obj/connectsock.o
#==================================================

#================ Executable Files ================
PROGRAM =  HTTP_Client HTTP_iServer
#==================================================

all: $(PROGRAM)

obj/%.o: src/%.c
	@gcc -Wall -c $< -o $@

HTTP_iServer: obj/HTTP_iServer.o $(SERVER_OBJ) $(HELPER_OBJ)
	gcc -Wall -o HTTP_iServer obj/HTTP_iServer.o $(SERVER_OBJ) $(HELPER_OBJ)

HTTP_Client: obj/HTTP_Client.o $(CLIENT_OBJ)
	gcc -Wall -o HTTP_Client obj/HTTP_Client.o $(CLIENT_OBJ)

clean:
	@rm -v obj/*.o $(PROGRAM)
	@echo "Do 'rm -rf download' to remove download folder"