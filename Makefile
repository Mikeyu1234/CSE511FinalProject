all: SERVER CLIENT

clean:
	rm -f client server *.o 

.PHONY:
	all clean

# we don't need that now.
#genmsg: msg.x
#	rpcgen -a -M msg.x

CLIENT: client.c psu_lock_mgt.c
	gcc -g  -o client client.c msg_clnt.c psu_lock_mgt.c msg_xdr.c -lrt -lpthread -lnsl

SERVER: server.c
	gcc -g  -o server server.c msg_svc.c  msg_xdr.c -lrt -lpthread -lnsl