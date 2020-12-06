#include <string.h>
#include <unistd.h>
#include <stdio.h>


int main(){

	printf("Long Max de argumentos: %li \n", sysconf(_SC_ARG_MAX));
    printf("Nº Max de hijos: %li \n", sysconf(_SC_CHILD_MAX));
    printf("Nº Max de ficheros: %li \n", sysconf(_SC_OPEN_MAX));

	return 1;
}

