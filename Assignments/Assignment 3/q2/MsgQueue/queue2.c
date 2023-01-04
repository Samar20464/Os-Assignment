#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define path1 "msgQueue"
#define path2 "idQueue"
struct msid1_ds *buff;

struct info
{
    /* data */
    int id;
    char data[10];
};

struct mesg {
    long messageType;
    struct info store[5];
} message;

struct bufferID {
    long messageType;
    char id[1];
} buffID;


int main()
{

    key_t k1, k2;

    printf("\n Acquiring Key ..");
    if((k1 = ftok(path1, 'd')) < 0){
        perror("Failed");
        abort();
    }
    printf("\nDone.\n");
    
    printf("\nReciving key  for Sending...");
    if((k2 = ftok(path2, 'd')) < 0){
        perror("Failed");
        abort();
    }
    printf("\nDone.\n");


    printf("\nReciever Created\n");
    
    printf("\nWaiting for Sender...\n");
    
    int msid1, msid2, i, lg = -1;

    printf("\nOpening Message Queue...\n");
    if ((msid1 = msgget(k1, 0666 | IPC_CREAT)) < 0)
    {
        perror("Failed");
        abort();
    }

    printf("\nMessage Queue for Send Back...");
    if ((msid2 = msgget(k2, 0666 | IPC_CREAT)) < 0)
    {
        perror("Failed");
        abort();
    }
    
    while (lg < 49)
    {

        struct info store[5];


        msgrcv(msid1, &message, sizeof(message), message.messageType, 0);
        int j =0;
        while(j<5)
        {
           if (message.store[j].id == lg + 1)
            {
                lg = message.store[j].id;
                printf("\nString is: %s, and id  is : %d ", message.store[j].data, message.store[j].id);
            }
            else
                break; 
        }
        
        printf("\n Recieved.\n");

        printf("\n  ID: %d\n", lg);

       

        buffID.messageType = 2;
        buffID.id[0] = lg;

        msgsnd(msid2, &buffID, sizeof(buffID), 0);
        printf("\nFeedback of ID Sended.\n");
    }

    msgctl(msid1, IPC_RMID, NULL);


    return 0;
}