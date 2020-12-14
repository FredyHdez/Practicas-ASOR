#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main (){

    mode_t umask(027);

    int fichero = open("/home/usuario_vms/Documentos/Pr2_ej7.txt", O_CREAT | O_RDONLY ,0750); 

    //printf("Descriptor: %i \n", fichero);

    return 1;
}