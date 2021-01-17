#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	//Control de errores
	if (argc < 2) {
		printf("Error");
		return -1;
	}

	//Variable 
	int fd;

	//Obtencion de la ruta
	char *HOME = getenv("HOME");
	char *tuberia = strcat(HOME, "/tuberia");

	printf("Home %s", tuberia);

	//Creacion de la tuberia
	mkfifo(tuberia, 0777);

	//Abrir para escritura
	fd = open(tuberia, O_WRONLY);

	write(fd, argv[1], strlen(argv[1]));

	close(fd);

	return 0;
}