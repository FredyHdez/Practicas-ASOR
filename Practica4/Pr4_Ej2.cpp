#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {

	//Variables
	int p_h;
	int h_p;
	int fdP[2];
	int fdH[2];
	pid_t pid;
	char *flagE;
	char *smsP;
	char *smsH;

	//Inicializacion (Tuberias, hijo)
	p_h = pipe(fdP);
	h_p = pipe(fdH);
	pid = fork();

	//

	switch (pid) {
	case -1:
		perror("fork()");
		return -1;

	case 0:
		//Hijo
		close(fdP[1]);
		close(fdH[0]);

		for (int i = 0; i < 10; i++) {

			ssize_t lec_Hijo = read(fdP[0], smsP, 255);
			smsP[lec_Hijo] = '\n';
			printf("(Hijo): %s \n", smsP);
			sleep(1);
			write(fdH[1], "1", 1);
			if (i == 9) {
				flagE = "q";
				write(fdH[1], &flagE, 1);

			}
		}

		break;

	default:
		//Padre
		close(fdP[0]);
		close(fdH[1]);

		while (flagE != "q") {

			//dup2(fdP[1], 0);

			printf("%s \n", "(Padre):");
			ssize_t lec_Padre = read(0, smsH, 255);
			smsH[lec_Padre] = '\n';
			write(fdP[1], smsH, 255);
			read(fdH[0], &flagE, 1);

		}

		wait(NULL);
		close(fdP[1]);
		close(fdP[0]);
		close(fdH[1]);
		close(fdH[0]);
		printf("Se han recibido 10 mensajes. \n");
		break;

	}

	return 0;
}