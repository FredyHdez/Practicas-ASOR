#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

	//Variables
	pid_t pid;
	pid_t ppid;
	pid_t pgid;
	pid_t psid;
	char* dirTrab;
	char* buff;

	pid = getpid();
	ppid = getppid();
	pgid = getpgid(pid);
	psid = getsid(pid);

	buff = (char*)malloc(sizeof(char) * 5000);
	dirTrab = getcwd(buff, 5000);

	//Salida por pantalla
	printf("El identificador del proceso es: %i \n", pid);
	printf("El identificador del proceso padre es: %i \n", ppid);
	printf("El identificador del grupo de procesos es: %i \n", pgid);
	printf("El identificador de sesion es: %i \n", psid);
	printf("El directorio de trabajo actual es: %s \n", dirTrab);

	free(buff);

	return 0;
}