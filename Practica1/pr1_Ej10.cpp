#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <pwd.h>

int main(){

    uid_t uid = getuid();

    printf("UID (Real): %d \n", getuid());
    printf("UID (Efectivo): %d \n", geteuid());

    struct passwd *pass = getpwuid(uid);

    printf("Nombre de Usuario: %s \n", pass->pw_name);
    printf("Home: %s \n", pass->pw_dir);    
    printf("Description: %s \n", pass->pw_gecos);

    return 1;
}
