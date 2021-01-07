#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

	//Control de errores 
	if (argc < 2) {

		printf("Error");
		return -1;

	}

	//Ejecucion del comando
	if (execv(argv[1], argv) == -1) {

		printf("Error");

	}
	else {

		printf("El comando termino de ejecutarse.");
	}

	return 0;
}