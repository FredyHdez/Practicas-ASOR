#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>

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

	fd_set dflectura;

	//Inicializamos los campos necesarios en hints
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC; //Tanto para ipv4 como para ipv6
	hints.ai_socktype = SOCK_DGRAM; //Tipo de conexion UDP
	hints.ai_flags = AI_PASSIVE;

	//Gestion de Errores
	if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {

		printf("ERROR ");
		return -1;

	}

	//Creamos el socket
	int socketUDP = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	//Establecemos la direccion para el socket
	if (bind(socketUDP, result->ai_addr, result->ai_addrlen) != 0) {

		printf("ERROR");
		return -1;

	}

	freeaddrinfo(result);

	socklen_t clientAddrlen = sizeof(clientAddr);

	//Inicializamos el descriptor de lectura
	int df = -1;

	//Gestion de los mensajes recibidos
	while (1) {


		while (df == -1) {

			FD_ZERO(&dflectura);
			FD_SET(socketUDP, &dflectura);
			FD_SET(0, &dflectura);
			df = select(socketUDP + 1, &dflectura, NULL, NULL, NULL);

		}

		time_t tiempo = time(NULL);
		struct tm *tm = localtime(&tiempo);
		size_t max;
		char s[50];

		if (FD_ISSET(socketUDP, &dflectura)) {

			ssize_t bytes = recvfrom(socketUDP, buf, 2, 0, (struct sockaddr *) &clientAddr, &clientAddrlen);

			getnameinfo((struct sockaddr *) &clientAddr, clientAddrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
			printf("[RED] %i byte(s) de %s:%s\n", bytes, host, serv);
			buf[1] = '\0';

			if (buf[0] == 't') {

				size_t bytesT = strftime(s, max, "%I:%M:%S %p", tm);
				s[bytesT] = '\0';

				sendto(socketUDP, s, bytesT, 0, (struct sockaddr *) &clientAddr, clientAddrlen);

			}
			else if (buf[0] == 'd') {

				size_t bytesT = strftime(s, max, "%Y-%m-%d", tm);
				s[bytesT] = '\0';

				sendto(socketUDP, s, bytesT, 0, (struct sockaddr *) &clientAddr, clientAddrlen);

			}
			else if (buf[0] == 'q') {

				printf("Salir\n");
				exit(0);

			}
			else {

				printf("Error\n", buf[0]);
			}

			//Gestion de mensajes con el descriptor
		}
		else {

			read(0, buf, 2);
			printf("[Consola] %i byte(s)\n", 2);
			buf[1] = '\0';

			if (buf[0] == 't') {

				size_t bytesT = strftime(s, max, "%I:%M:%S %p", tm);
				s[bytesT] = '\0';

				printf("%s\n", s);

			}
			else if (buf[0] == 'd') {

				size_t bytesT = strftime(s, max, "%Y-%m-%d", tm);
				s[bytesT] = '\0';

				printf("%s\n", s);

			}
			else if (buf[0] == 'q') {

				printf("Saliendo...\n");
				exit(0);

			}
			else {

				printf("Error\n", buf[0]);
			}
		}
	}

	return 0;
}