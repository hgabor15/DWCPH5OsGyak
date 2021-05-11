#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

 
void sig_handler(int signum){
 
    printf("%lu\n", sizeof(int));
    while(1){}
}
 
int main(){
    pid_t pid = getpid();
    printf("pid: %d\n", pid);
    signal(SIGTERM,sig_handler);
    while(1){}
return 0;
}
