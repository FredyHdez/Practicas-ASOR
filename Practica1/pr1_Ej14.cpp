#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(){

    time_t tm =time(NULL);
    struct tm *info = localtime(&tm);

    int year = info->tm_year;

    printf("El año actual es: %i \n", 1900 + year);

    return 1;
}
