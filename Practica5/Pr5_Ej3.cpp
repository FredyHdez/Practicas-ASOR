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

	char buf[2];
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];

	struct sockaddr_storage clientAddr;

	//Inicializamos los campos necesarios en hints
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; //Tanto para ipv4 como para ipv6
	hints.ai_socktype = SOCK_DGRAM; //Tipo de conexion UDP
	hints.ai_flags = AI_PASSIVE;

	//Gestion de errores
	if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {

		printf("ERROR ");
		return -1;

	}

	//Creamos el socket
	int socketUDP = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	freeaddrinfo(result);

	socklen_t clientAddrlen = sizeof(clientAddr);
	sendto(socketUDP, argv[3], 2, 0, result->ai_addr, result->ai_addrlen);

	printf("%s\n", argv[3]);


	if (*argv[3] == 'd' || *argv[3] == 't') {

		char s[50];
		ssize_t bytes = recvfrom(socketUDP, s, 50, 0, (struct sockaddr *) &clientAddr, &clientAddrlen);
		s[bytes] = '\0';

		printf("%s\n", s);

	}

	return 0;
}