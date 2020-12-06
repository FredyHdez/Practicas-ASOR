#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(){

    struct timeval timeV;

    int timeOD = gettimeofday(&timeV, NULL);
    int start = timeV.tv_usec;

    for (int i = 0; i < 1000000; i++);

    int timeOD2 = gettimeofday(&timeV, NULL);
    int end = timeV.tv_usec;

    printf("El tiempo del bucle ha sido: %i ms \n", end - start);

    return 1;
}
