#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static volatile int stp = 0;

void stpBorrado(int s) {

	if (s == SIGUSR1) {

		stp = 1;

	}
}

int main(int argc, char *argv[]) {

	//Control de errores 
	if (argc < 2) {

		printf("Error \n");
		return -1;

	}

	//Variables
	struct sigaction manSignal;
	int sec;

	//Inicializacion de variables
	manSignal.sa_handler = stpBorrado;
	manSignal.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &manSignal, NULL);
	sec = atoi(argv[1]);
	int i = 0;

	while (stp == 0 && 1 < sec) {

		sleep(1);
		i++;

	}


	if (stp == 1) {

		printf("El ejecutable no sera borrado \n");

	}
	else {

		printf("Se va ha borrar el ejecutable \n");
		unlink(argv[0]);

	}

	return 0;
}