#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[]) {

	//Control de errores

	if (argc < 2) {

		printf("Error");
		return -1;
	}

	struct stat buff;

	int valorStat = stat(argv[1], &buff);

	//Control de errores de stat

	if (valorStat == -1) {

		printf("Error: Directorio erroneo");
		return -1;
	}

	//Impresion de informacion

	printf("Major: %li \n", major(buff.st_dev));
	printf("Minor: %li \n", minor(buff.st_dev));
	printf("I-node: %li \n", buff.st_ino);

	mode_t type = buff.st_mode;
	printf("Tipo: %li \n", type);

	if (S_ISLNK(type)) {
		printf("%s es un enlace simbolico. \n", argv[1]);
	}
	else if (S_ISREG(type)) {
		printf("%s es un fichero ordinario. \n", argv[1]);
	}
	else if (S_ISDIR(type)) {
		printf("%s es un directorio. \n", argv[1]);
	}

	time_t time = buff.st_atime;

	struct tm *ptrTime = localtime(&time);

	printf("Ultimo Acceso: %d:%d \n", ptrTime->tm_hour, ptrTime->tm_min);

	return 0;
}