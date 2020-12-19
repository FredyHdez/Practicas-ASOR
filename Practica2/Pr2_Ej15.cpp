#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {

	//Control de errores

	if (argc < 2) {

		printf("Error \n");
		return -1;
	}

	int fd = open(argv[1], O_CREAT | O_RDWR, 0777);

	if (fd == -1) {

		printf("No se ha creado o abierto el fichero \n");
		return -1;

	}

	//Inicializar lock

	struct flock lock;

	lock.l_type = F_UNLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();


	//Ponemos el cerrojo
	int statLock = fcntl(fd, F_GETLK, &lock);

	if (lock.l_type == F_UNLCK) {

		printf("Cerrojo desbloqueado \n"); //Hay que bloquearlo 30 sec

		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_pid = getpid();

		if (fcntl(fd, F_GETLK, &lock) == -1) {

			printf("No se ha bloqueado el cerrojo \n");
			close(fd);
			return -1;

		}
		else {

			//Cerrojo Bloqueado
			printf("Cerrojo Bloqueado \n");

			//Obtenemos la hora para poder ponerla
			time_t timeLock = time(NULL);
			struct tm *tm = localtime(&timeLock);
			char buff[500];
			strftime(buff, 500, "%A, %d de %B de  %Y, %R \n", localtime(&timeLock));

			//Bloqueamos la ejecucion 30 sec
			sleep(30);

			lock.l_type = F_WRLCK;
			lock.l_whence = SEEK_SET;
			lock.l_start = 0;
			lock.l_len = 0;
			lock.l_pid = getpid();


			//Desbloquemos cerrojo
			if (fcntl(fd, F_GETLK, &lock) == -1) {

				printf("ERROR:No se ha podido desbloquear el cerrojo\n");
				close(fd);
				return 1;

			}
			else {

				close(fd);

			}

			close(fd);
		}

	}
	else {

		//Como el cerrojo esta bloqueado terminamos el programa
		printf("Cerrojo bloqueado\n");
		return 0;

	}

	close(fd);

	return 0;
}