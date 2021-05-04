#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 0x1111

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

struct sembuf p = { 0, -1, SEM_UNDO};
struct sembuf v = { 0, +1, SEM_UNDO};

int main()
{
    int nsems, semnum, rtn, semflg, cmd; 
    unsigned nsops;  
	struct sembuf sembuf, *sop; 

    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    if(id < 0)
    {
        perror("semget"); exit(11);
    }
    union semun u;
    u.val = 1;
    if(semctl(id, 0, SETVAL, u) < 0)
    {
        perror("semctl"); exit(12);
    }
    int pid;
    pid =  fork();
    srand(pid);
    if(pid < 0)
    {
        perror("fork"); exit(1);
    }
    else if(pid)
    {

        semnum=0;
        cmd = SETVAL;
        u.val=1;
        rtn = semctl(id, semnum, cmd, u);
    }
    else
    {
        nsems=1;
	    semflg = 00666 | IPC_CREAT;   
        id=semget (KEY, nsems, semflg);
	    if (id < 0 ) {perror(" semget hiba"); exit(0);}
	    else printf("\n semid: %d ",id);
        for(int i=0; i<3; i++){
            nsops = 1;	
	        sembuf.sem_num = 0;
	        sembuf.sem_op = 1;
	        sembuf.sem_flg = 0666;
	        sop = &sembuf;	
	        rtn = semop(id, sop, nsops);
            sleep(2);
            printf("Pid: %d \n", id);
            nsops = 1;	
	        sembuf.sem_num = 0;
	        sembuf.sem_op = -2;
	        sembuf.sem_flg = SEM_UNDO;
	        sop = &sembuf;	
	        rtn = semop(id, sop, nsops);
	        scanf("%d", &nsems);
        }
        nsems = 1;
	    semflg = 00666 | IPC_CREAT;
	    id = semget (KEY, nsems, semflg);
	    if (id < 0 ) {perror(" semget hiba"); exit(0);}
	    else printf("\n semid: %d ",id);
	    printf ("\n");

	    cmd = IPC_RMID;		/* Ez a megszuntetes parancsa */
	    rtn = semctl(id,0, cmd, u);        
        }
    }
