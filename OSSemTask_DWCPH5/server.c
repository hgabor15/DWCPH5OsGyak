#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

int fd;


void sig_handler(int signum) {
    if (signum == SIGTERM){
        close(fd);
        exit(0);
    }
}

int main() {


    pid_t p = getpid();
    printf("A pid: %d\n", p);
    
    int signum;
    char * DWCPH5 = "/tmp/DWCPH5";
    mkfifo(DWCPH5, 0666);
    fd = open(DWCPH5, O_RDONLY);
    char arr[80];
    FILE *fp;
    int n=0;

    if (signal(SIGTERM, sig_handler) == SIG_ERR)
    printf("\ncan't catch SIGTERM");

    while (1)
    {   
        read(fd, arr, sizeof(arr));
        fp = fopen("text.txt", "a");
        fprintf(fp, "%d %s\n", n, arr);
        fclose(fp);
        n++;
    }

}
