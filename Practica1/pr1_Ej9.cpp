#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

int main(){

    printf("UID (Real): %d \n", getuid());
    printf("UID (Efectivo): %d \n", geteuid());

    return 1;
}
