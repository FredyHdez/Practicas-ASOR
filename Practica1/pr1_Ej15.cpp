#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(){

    time_t tm =time(NULL);
    struct tm *info = localtime(&tm);

    int year = info->tm_year;
    char day[10];
    strftime(day, 100, "%A", info);
    char month[15];
    strftime(month, 100, "%B", info);

    printf("Hoy es : %s, %i de %s de %i, %i:%i \n", day, info->tm_mday, month, 1900+year, info->tm_hour, info->tm_min );

    return 1;
}
