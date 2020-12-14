#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main (){

    int fichero = open("/home/usuario_vms/Documentos/Pr2_ej5.txt", O_CREAT ,0645);

    printf("Descriptor: %i \n", fichero);
}