#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char**argv) {

	//control de errores
	if (argc < 2) {

		printf("ERROR\n");
		return -1;

	}

	//Variables
	struct addrinfo hints;
	struct addrinfo *result, *iterator;

	char buf[81];
	int cliSd;
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];

	char buffIn[256];
	char buffOut[256];
	ssize_t c;


	//Inicializamos los campos necesarios en hints
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; //Tanto para ipv4 como para ipv6
	hints.ai_socktype = SOCK_STREAM; //Tipo de conexion TCP
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {

		printf("ERROR ");
		return -1;

	}

	//Creamos el socket
	int socketTCP = socket(result->ai_family, result->ai_socktype, 0);

	connect(socketTCP, (struct sockaddr *)result->ai_addr, result->ai_addrlen);

	freeaddrinfo(result);

	while (1) {

		c = read(0, buffOut, 255);
		buffOut[c] = '\0';
		send(socketTCP, buffOut, c, 0);


		if ((buffOut[1] == 'q') && (c == 2)) {

			printf("Conexión terminada\n");
			break;

		}

		c = recv(socketTCP, buffIn, 255, 0);
		buffIn[c] = '\0';
		printf("[OUT]:%s\n", buffIn);

	}

	close(socketTCP);

	return 0;
}