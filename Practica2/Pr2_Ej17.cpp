#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	//Control de errores

	if (argc < 2) {

		printf("Error");
		return -1;
	}

	DIR *drtr = opendir(argv[1]);

	if (drtr == NULL) {

		printf("Error al abrir el directorio \n");
		return -1;

	}


	struct stat fdStat;
	int valorStat = stat(argv[1], &fdStat);

	//Error
	if (valorStat < 0) {

		printf("Error");
		return -1;

	}


	struct dirent* readFd;
	while (readFd = readdir(drtr)) {

		//atributos de fichero
		lstat(readFd->d_name, &fdStat);

		if (S_ISDIR(fdStat.st_mode)) {
			//Directorio
			printf("%s / \n", readFd->d_name);

		}
		else if (S_ISREG(fdStat.st_mode)) {
			//Fichero normal
			printf("%s \n", readFd->d_name);

		}
		else if (S_ISLNK(fdStat.st_mode)) {
			//Enlace Simbolico
			char* route = (char*)malloc(sizeof(char)* (strlen(argv[1]) + strlen(readFd->d_name) + 5));
			strcpy(route, argv[1]);
			strcat(route, " -> ");
			strcat(route, readFd->d_name);
			char* symName = (char*)malloc(fdStat.st_size + 1);
			readlink(route, symName, fdStat.st_size + 1);
			printf("%s -> %s \n", readFd->d_name, symName);

		}
		else if ((fdStat.st_mode & S_IEXEC) != 0) {
			//Ejecutable
			printf("%s *\n", readFd->d_name);

		}

	}

	return 0;
}