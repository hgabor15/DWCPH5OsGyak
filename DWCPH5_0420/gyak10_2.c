#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#define MSGKEY 654321L

struct msgbuf1 {		
	long mtype1;
	char mtext1[512];
} sndbuf, *msgp1;

struct msgbuf2 {
	long mtype2;
	char mtext2[512];
} rcvbuf2, *msgp2;

struct msqid_ds ds, *buf;

int main()
{   
    pid_t pid = fork();
    int x = 1;
    int msgid;		
	key_t key;		
	int msgflg;		
	int rtn, msgsz;	

    if(pid<0)   {
        fprintf(stderr, "Fork failed");
        return 1;    
    }

    else if(pid == 0)
        {      
	            	int msgid;		
	                key_t key;		
	                int msgflg;		
	                int rtn, msgsz;		
	                
	                key = MSGKEY;
	                msgflg = 00666 | IPC_CREAT;
	                msgid = msgget( key, msgflg);
                 	if ( msgid == -1) {
                                perror("\n The msgget system call failed!");
                                exit(-1);
                        }
	                printf("\n Az msgid %d, %x : ", msgid,msgid);

	                msgp1        = &sndbuf;
	                msgp1->mtype1 = 1;   			
                 	strcpy(msgp1->mtext1,"Egyik uzenet");
	                msgsz       = strlen(msgp1->mtext1) + 1;
                    rtn = msgsnd(msgid,(struct msgbuf1 *) msgp1, msgsz, msgflg);

	                strcpy(msgp1->mtext1,"Masik uzenet");
	                msgsz       = strlen(msgp1->mtext1) + 1;
	                rtn = msgsnd(msgid,(struct msgbuf1 *) msgp1, msgsz, msgflg);
	                printf("\n");

	                exit (0);
        }
    else
    {
        wait(NULL);
        int a;
        long mtype2;
        int msgid;		
	    key_t key;		
	    int mtype, msgflg;	
	    int rtn, msgsz;
        printf("(1)darabszam,(2)olvas1,(3)olvasall: ");
        scanf("%d",&a);
        if(a==1){
            msgp2 = &rcvbuf2;		
	        buf = &ds;		
	        msgsz = 20;
	        mtype2 = 0;	
	        rtn = msgctl(msgid,IPC_STAT,buf);
	        printf("Az uzenetek szama: %lun\n",buf->msg_qnum);}
        else if(a==2){
	            key = MSGKEY;	
	            msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	            msgid = msgget( key, msgflg);    
             	if ( msgid == -1) {
                            perror("\n The msgget system call failed!");
                            exit(-1);
                    }
	            printf("\n Az msgid: %d",msgid);

	            msgp2 = &rcvbuf2;		
	            buf = &ds;		
	            msgsz = 20;
	            mtype = 0;	
	            rtn = msgctl(msgid,IPC_STAT,buf);
	            printf("\n Az uzenetek szama: %lun",buf->msg_qnum);
	            
	            
	            rtn = msgrcv(msgid,(struct msgbuf *)msgp2, msgsz, mtype, msgflg);
	            printf("\n Az rtn: %d,  a vett uzenet:%s\n",rtn, msgp2->mtext2);
	            rtn = msgctl(msgid,IPC_STAT,buf);
        }
        else if(a==3){
	            key = MSGKEY;	
	            msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	            msgid = msgget( key, msgflg);    
             	if ( msgid == -1) {
                            perror("\n The msgget system call failed!");
                            exit(-1);
                    }
	            printf("\n Az msgid: %d",msgid);

	            msgp2 = &rcvbuf2;		
	            buf = &ds;		
	            msgsz = 20;
	            mtype = 0;	
	            rtn = msgctl(msgid,IPC_STAT,buf);
	            printf("\n Az uzenetek szama: %lun",buf->msg_qnum);
	            
	            while (buf->msg_qnum) {
	            rtn = msgrcv(msgid,(struct msgbuf *)msgp2, msgsz, mtype, msgflg);
	            printf("\n Az rtn: %d,  a vett uzenet:%s\n",rtn, msgp2->mtext2);
	            rtn = msgctl(msgid,IPC_STAT,buf);
        }
    }
    }
}



