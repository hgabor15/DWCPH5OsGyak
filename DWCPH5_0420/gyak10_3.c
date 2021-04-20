#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#define SHMKEY 123456L

struct vmi {
		int  hossz;
		char szoveg[512-sizeof(int)];
	} *segm;	

int main()
{   
    pid_t pid = fork();
   	int shmid;		
	key_t key;		
	int size=512;		
	int shmflg;
    int rtn;		
	int cmd;

    if(pid<0)   {
        fprintf(stderr, "Fork failed");
        return 1;    
    }

    else if(pid == 0) {
        key = SHMKEY;
	    shmflg = 0;
	    if ((shmid=shmget( key, size, shmflg)) < 0) {
	       printf("\n Nincs meg szegmens! Keszitsuk el!");
	       shmflg = 00666 | IPC_CREAT;
	       if ((shmid=shmget( key, size, shmflg)) < 0) {
	          perror("\n Az shmget system-call sikertelen!");
	          exit(-1);
	       }
	    } else printf("\n Van mar szegmens!");

	    printf("  Az shmid azonositoja %d: \n", shmid);
    }
    else {
    wait(NULL);
    key = SHMKEY;
	shmflg = 0;
	if ((shmid=shmget( key, size, shmflg)) < 0) {
	    perror("\n Az shmget system-call sikertelen!");
	    exit(-1);
	}

	shmflg = 00666 | SHM_RND;
	segm = (struct vmi *)shmat(shmid, NULL, shmflg); 
	if (segm == (void *)-1) {
		perror(" Sikertelen attach");
		exit (-1);
	}

	if (strlen(segm->szoveg) > 0) 
		printf("\n Regi szoveg: %s (%d hosszon)",segm->szoveg,segm->hossz);
 
	printf("\n Uj szoveget kerek!\n");
    scanf("%str", segm->szoveg);
	printf("\n Az uj szoveg: %s\n",segm->szoveg);
	segm->hossz=strlen(segm->szoveg);
		
	shmdt(segm);
    struct shmid_ds shmid_ds, *buf; 
	buf = &shmid_ds;

	key = SHMKEY;
	shmflg = 0;
	if ((shmid=shmget( key, size, shmflg)) < 0) {
	    perror("\n Az shmget system-call sikertelen!");
	    exit(-1);
	}

	do {
	printf("\n Add meg a parancs szamat ");
	printf("\n 0 IPC_STAT (status) ");
	printf("\n 1 IPC_RMID (torles)   >  ");
    printf("\n 2 EXIT   >  ");
	scanf("%d",&cmd);
	} while (cmd < 0 && cmd > 2);

	switch (cmd)
	{
	case 0: rtn = shmctl(shmid, IPC_STAT, buf);
		printf("\n  Segm. meret: %ld",buf->shm_segsz);
		printf("\n  Utolso shmop-os proc. pid: %d\n ",buf->shm_lpid);
		break;
	case 1: rtn = shmctl(shmid, IPC_RMID, NULL);
		printf("\n Szegmens torolve\n");
    case 2: exit(0);
        }
	}
	
	exit(0);
    
}

