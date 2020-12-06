#include <stdio.h>
#include <time.h>

int main(){
    time_t vTime = time(NULL);
    printf("Time (Epoch): %li \n", vTime);

}
