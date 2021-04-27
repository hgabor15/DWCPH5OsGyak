#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>
#define SEMKEY 123456L

int main()
{
    
	int semid,nsems,rtn;
	int semflg;
	struct sembuf sembuf, *sop;
	union semun {
       int val;
       struct semid_ds *buf;
       unsigned short *array;
    } arg;
	int cmd;
	nsems = 1;
	semflg = 00666 | IPC_CREAT;
	semid = semget (SEMKEY, nsems, semflg);
	if (semid < 0 ) {perror(" semget hiba"); exit(0);}
	else printf("\n semid: %d ",semid);
	printf ("\n");

	cmd = IPC_RMID;		/* Ez a megszuntetes parancsa */
	rtn = semctl(semid,0, cmd, arg);

	printf("\n kill rtn: %d ",rtn);
	printf("\n");

}
