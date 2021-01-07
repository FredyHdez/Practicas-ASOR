#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

	//Control de errores 
	if (argc < 2) {

		printf("Error \n");
		return -1;

	}

	//Ejecucion del comando
	if (system(argv[1]) == -1) {

		printf("Error: El comando no ha podido ejecutarse \n");

	}
	else {

		printf("El comando termino de ejecutarse. \n");
	}

	return 0;
}