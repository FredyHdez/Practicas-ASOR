#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(){

    char *s;
    if (setuid(0) == -1){
        printf("Error(es):%s \n", errno, strerror(errno));
    }
    
    return 1;
}
