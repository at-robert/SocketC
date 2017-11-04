all : client.c server.c
	gcc -Wall -g -o client client.c
	gcc -Wall -g -o server server.c

clean :
	rm client
	rm server