#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main (){

    mode_t umask(027);

    int fichero = open("/home/usuario_vms/Documentos/Pr2_ej7", O_CREAT,0777); 


    return 1;
}