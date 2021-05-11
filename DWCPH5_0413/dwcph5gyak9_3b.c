#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

 
void sig_handler(int signum){
 
    printf("DWCPH5\n");
    
    printf("Process paused");
    _Exit(1);
}
 
int main(){
    pid_t pid = getpid();
    printf("pid: %d\n", pid);
    signal(SIGALRM,sig_handler); // Register signal handle
    for(int i=1;;i++){
    sleep(1);  // Delay for 1 second
}
return 0;
}
