#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static volatile int contSInt;
static volatile int contSTstp;

void contar(int s) {

	if (s == SIGINT) {

		contSInt++;

	}

	if (s == SIGTSTP) {

		contSTstp++;

	}

}

int main(int argc, char *argv[]) {

	//Variables
	struct sigaction manSignal;



	//Inicializacion de variables
	manSignal.sa_handler = contar;
	manSignal.sa_flags = SA_RESTART;
	sigaction(SIGINT, &manSignal, NULL);
	sigaction(SIGTSTP, &manSignal, NULL);

	while (contSInt < 10 && contSTstp < 10) {

	}

	printf("SIGINT capturada %i veces \n", contSInt);
	printf("SIGTSTP capturada %i veces \n", contSTstp);

	return 0;
}