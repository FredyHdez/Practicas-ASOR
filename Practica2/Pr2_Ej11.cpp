#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	//Control de errores

	if (argc < 2) {

		printf("Error \n");
		return -1;
	}

	struct stat buff;

	int valorStat = stat(argv[1], &buff);

	//Control de errores de stat

	if (valorStat == -1) {

		printf("Error: Directorio erroneo \n");
		return -1;
	}


	char* rgd;
	rgd = (char*)malloc(sizeof(char)*(5 + strlen(argv[1])));
	char* simb;
	simb = (char*)malloc(sizeof(char)*(5 + strlen(argv[1])));

	//Comprobar que es un fichero ordinario y crear los enlaces si lo es

	mode_t type = buff.st_mode;

	if (S_ISREG(type)) {

		strcpy(rgd, argv[1]);
		rgd = strcat(rgd, ".hard");

		if (link(argv[1], rgd) == -1) {
			printf("No se pudo crear el enlace rigido \n");
		}
		else {
			printf("Se pudo crear el enlace duro \n");
		}

		strcpy(simb, argv[1]);
		simb = strcat(simb, ".sym");

		if (symlink(argv[1], simb) == -1) {
			printf("No se pudo crear el enlace simbolico \n");
		}
		else {
			printf("Se pudo crear el enlace simbolico \n");
		}

	}
	else {
		printf("No es un fichero ordinario \n");
	}

	return 0;
}