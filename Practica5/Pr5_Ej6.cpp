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

	struct sockaddr_storage cli;
	socklen_t clen = sizeof(cli);

	char buf[81];
	int cliSd;
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];
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

	//Establecemos la direccion para el socket
	if (bind(socketTCP, result->ai_addr, result->ai_addrlen) != 0) {

		printf("ERROR");
		return -1;

	}

	freeaddrinfo(result);

	listen(socketTCP, 5);

	while (1) {

		cliSd = accept(socketTCP, (struct sockaddr *) &cli, &clen);

		while (1) {

			getnameinfo((struct sockaddr *)&cli, clen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
			printf("Conexión desde %s:%s\n", host, serv);

			c = recv(cliSd, buf, 80, 0);
			buf[c] = '\0';

			if ((buf[0] == 'Q') && (c == 2)) {

				printf("Conexión terminada\n");
				break;

			}

			send(cliSd, buf, c, 0);

		}

	}

	close(cliSd);


	return 0;
}