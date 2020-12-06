#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>


int main(){

    char *s;
    if (setuid(0) == -1){
        perror(s);
    }
    return 1;
}


