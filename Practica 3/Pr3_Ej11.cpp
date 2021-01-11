#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char *argv[]) {

	sigset_t signal;
	sigset_t signalPend;

	//Inicializar señales
	sigemptyset(&signal);
	sigaddset(&signal, SIGINT);
	sigaddset(&signal, SIGTSTP);

	//Bloqueamos las señales
	sigprocmask(SIG_BLOCK, &signal, NULL);

	//Obtenemos Sleep_Secs
	char *sleepSec = getenv("SLEEP_SECS");
	int sec = atoi(sleepSec);

	printf("Suspendemos la ejecucion\n");
	sleep(sec);

	//Comprobar la recepcion de señales 
	sigpending(&signalPend);

	if (sigismember(&signalPend, SIGINT) == 1) {

		printf("Señal SIGINT recibida\n");
		sigdelset(&signal, SIGINT);

	}
	else {
		printf("Señal SIGINT no ha sido recibida\n");
	}

	if (sigismember(&signalPend, SIGTSTP) == 1) {

		printf("Señal SIGTSTP recibida\n");
		sigdelset(&signal, SIGTSTP);

	}
	else {
		printf("Señal SIGTSTP no ha sido recibida\n");
	}

	//Desbloqueamos las señales 
	sigprocmask(SIG_UNBLOCK, &signal, NULL);

	return 0;
}