all:
	rpcgen -C FileReadWrite.x
	gcc -o client client.c FileReadWrite_clnt.c FileReadWrite_xdr.c Timer.c -lnsl
	gcc -o server_tcp server_tcp.c FileReadWrite_svc.c FileReadWrite_xdr.c -lnsl
	gcc -o server_udp server_udp.c FileReadWrite_svc.c FileReadWrite_xdr.c -lnsl

clean:
	rm client server_udp server_tcp FileReadWrite_* FileReadWrite.h
