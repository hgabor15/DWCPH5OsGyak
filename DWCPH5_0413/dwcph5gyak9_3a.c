#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

char *a = argv[1];
int num = atoi(a);
kill(num, SIGALRM);
return 0;

}
