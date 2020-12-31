#include <sched.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

	//Control de errores 

	if (argc < 2) {

		printf("Error \n");
		return -1;

	}

	//Conseguir tipo de planificacion
	int pid;
	pid = atoi(argv[1]);

	int plan;
	plan = sched_getscheduler(pid);

	if (plan == SCHED_OTHER) {

		printf("El planificador es Other \n");

	}
	else if (plan == SCHED_FIFO) {

		printf("El planificador es FIFO \n");

	}
	else {

		printf("El planificador es RR (Round Robin) \n");

	}

	//Conseguir prioridad y sus rangos
	int prio;
	struct sched_param param;
	prio = sched_getparam(pid, &param);

	printf("La prioridad de proceso es: %i \n", param.sched_priority);

	int min;
	int max;
	max = sched_get_priority_max(plan);
	min = sched_get_priority_min(plan);

	printf("El valor maximo es %i \n", max);
	printf("El valor minimo es %i \n", min);

	return 0;
}