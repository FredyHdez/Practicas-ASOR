#include <sys/utsname.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(){

	struct utsname infoSys;

    if (uname (&infoSys) == -1){
            printf("Error(%d): %s \n", errno, strerror(errno));
            return-1;
    } else {
            printf("Nombre del SO: %s \n", infoSys.sysname);
            printf("Nombre del Host: %s \n", infoSys.nodename);
            printf("Release del SO: %s \n", infoSys.release);
            printf("Version del SO: %s \n", infoSys.version);
            printf("Hardware: %s \n", infoSys.machine);
            printf("Dominio: %s \n", infoSys.domainname);
        }
	return 1;
}

