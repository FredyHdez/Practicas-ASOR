#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

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

	int fd2 = dup2(fd, 1);

	printf("Redirigido a %d \n", argv[1]);

	dup2(fd2, fd);

	return 0;
}