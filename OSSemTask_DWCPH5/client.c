//Meg kell adni argumentumban a server PID-jét
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

int main( int argc, char *argv[]) {
    
    int fd;
    int a=0;
    char * DWCPH5 = "/tmp/DWCPH5";
    char arr[80];
    int arg1 = atoi(argv[1]);
    

    printf("(1) Beolvas:\n (2) Kilép:\n");
    do {
        scanf("%d", &a);
        if(a==1) {
                fd = open(DWCPH5, O_WRONLY);
                fgets(arr, 80, stdin);
                write(fd, arr, strlen(arr)+1);
        }
        else if(a==2) {
            printf("%d\n", arg1);
            kill(arg1, SIGTERM);
            exit(0);
        }
        else
            printf("Nem jót választott, próbálja újra\n");
    } while(a>1 || a<2);
}
