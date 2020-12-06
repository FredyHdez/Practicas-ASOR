#include <string.h>
#include <unistd.h>
#include <stdio.h>


int main(){

	printf("Nª Max de enlaces: %li \n", pathconf(0, _PC_LINK_MAX));
    printf("Tam Max nombre de ruta: %li \n", pathconf(0, _PC_PATH_MAX));
    printf("Tam Max de nombre de ficheros: %li \n", pathconf(0, _PC_NAME_MAX));

	return 1;
}
