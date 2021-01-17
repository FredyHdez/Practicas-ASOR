#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {

	//variables
	char *tuberia;
	char *tuberia2;
	char buff[257];
	int tub1;
	int tub2;
	int tubAct;
	int slct;

	//inicializar
	tuberia = "tuberia";
	tuberia2 = "tuberia2";

	//Crear tuberias 
	mkfifo(tuberia, 0644);
	mkfifo(tuberia2, 0644);

	//Abrir tuberias
	tub1 = open(tuberia, O_RDONLY | O_NONBLOCK);
	tub2 = open(tuberia2, O_RDONLY | O_NONBLOCK);

	//Control de errores 
	if (tub1 == -1 || tub2 == -1) {

		printf("Error");
		return -1;

	}

	while (slct != -1) {

		//preparar conjunto de descriptores
		fd_set cnjtDesc;
		FD_ZERO(&cnjtDesc);
		FD_SET(tub1, &cnjtDesc);
		FD_SET(tub2, &cnjtDesc);
		int numTubAct;

		slct = select((tub1 < tub2) ? tub2 + 1 : tub1 + 1, &cnjtDesc, NULL, NULL, NULL);

		if (slct > 0) {

			if (FD_ISSET(tub1, &cnjtDesc)) {

				numTubAct = 1;
				tubAct = tub1;

			}
			else {

				numTubAct = 2;
				tubAct = tub2;

			}

			ssize_t readSize = 256;

			while (readSize == 256) {

				readSize = read(tubAct, buff, 256);
				buff[readSize] = '\0';
				printf("Tuberia %i: %s", numTubAct, buff);

			}

			if (readSize != 256 && numTubAct == 1) {

				close(tub1);
				tub1 = open(tuberia, O_RDONLY | O_NONBLOCK);
				//Control de errores
				if (tub1 == -1) {

					close(tub1);
					close(tub2);
					return-1;

				}

			}
			else if (readSize != 256 && numTubAct == 2) {

				close(tub2);
				tub2 = open(tuberia2, O_RDONLY | O_NONBLOCK);
				//Control de errores
				if (tub2 == -1) {

					close(tub1);
					close(tub2);
					return-1;

				}
			}
		}
	}


	close(tub1);
	close(tub2);
	return 0;
}