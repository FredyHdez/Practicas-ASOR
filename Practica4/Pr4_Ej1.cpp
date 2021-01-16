#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

	//control de errores
	if (argc < 5) {
		printf("Error");
	}

	//Variables
	int tub;
	int fd[2];
	pid_t pid;

	//Inicializacion
	tub = pipe(fd);
	pid = fork();

	//

	switch (pid) {
	case -1:
		perror("fork()");
		return -1;

	case 0:
		//Hijo
		dup2(fd[1], 1);

		close(fd[1]);
		close(fd[0]);

		execlp(argv[1], argv[1], argv[2], NULL);

		break;

	default:
		//Padre
		dup2(fd[0], 0);

		close(fd[0]);
		close(fd[1]);

		execlp(argv[3], argv[3], argv[4], NULL);
		break;

	}

	return 0;
}