#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>


int main(int argc, char *argv[]) {


	//Variables
	pid_t pid;
	pid_t gpid;
	pid_t ppid;
	pid_t pgid;
	pid_t psid;
	pid_t sid;
	char* dirTrab;
	char* buff;
	int newDir;


	//Inicializacion
	pid = fork();


	switch (pid) {
	case -1:
		//Error
		perror("fork");
		exit(-1);
		break;

	case 0:
		//Crear sesion
		sid = setsid();

		//Cambiar directorio
		newDir = chdir("/tmp");

		//Obtencion de la informacion de los procesos
		gpid = getpid();
		ppid = getppid();
		pgid = getpgid(gpid);
		psid = getsid(gpid);

		//Numero maximo de ficheros?
		buff = (char*)malloc(sizeof(char) * 5000);
		dirTrab = getcwd(buff, 5000);

		//Salida por pantalla
		printf("Hijo %i (padre: %i)\n", gpid, ppid);
		printf("El identificador del proceso es: %i \n", gpid);
		printf("El identificador del proceso padre es: %i \n", ppid);
		printf("El identificador del grupo de procesos es: %i \n", pgid);
		printf("El identificador de sesion es: %i \n", psid);
		printf("El directorio de trabajo actual es: %s \n", dirTrab);

		free(buff);


		break;

	default:
		//Obtencion de la informacion de los procesos
		gpid = getpid();
		ppid = getppid();
		pgid = getpgid(gpid);
		psid = getsid(gpid);

		//Numero maximo de ficheros?
		buff = (char*)malloc(sizeof(char) * 5000);
		dirTrab = getcwd(buff, 5000);

		//Salida por pantalla
		printf("Padre %i (hijo: %i)\n", gpid, ppid);
		printf("El identificador del proceso es: %i \n", gpid);
		printf("El identificador del proceso padre es: %i \n", ppid);
		printf("El identificador del grupo de procesos es: %i \n", pgid);
		printf("El identificador de sesion es: %i \n", psid);
		printf("El directorio de trabajo actual es: %s \n", dirTrab);

		free(buff);


		break;

	}

	sleep(3);
	return 0;
}