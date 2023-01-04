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


struct info
{
    /* data */
    int id;
    char info[10];
};


struct mesg {
    long messageType;
    struct info store[5];
} message;


struct BufferID {
    long messageType;
    char id[1];
} idBuffer;


void RandomString(int n, char *res)
{

    char alphab[26] = "abcdefghijklmnopqrstuvwxyz";
    char dig[2];
    int i =0;
    while(i< n)
    {
        snprintf(dig, 2, "%c", alphab[rand() % 26]);
        strcat(res, dig);
        i++;
    }
}

void copy(char *arr[50])
{


for (int i = 0; i < 50; i++)
    {
        int lenGth = 10;
        char in[10];
        strcpy(in, "");
        arr[i] = malloc(10 * sizeof(char));
        RandomString(lenGth, in);
        strcpy(arr[i], in);
    }
}

int main()
{
    
    char *arr[50];
    copy(arr);

  

    key_t k1, k2;

    printf("\nSender: cquiring k1...");
    if((k1 = ftok(path1, 'd'))  < 0){
        perror("Failed");
        abort();
    }
    printf("\nAcquiration Done.\n");

    printf("\nSender: cquiring k2...");
   if((k2 = ftok(path1, 'd'))  < 0){
        perror("Failed");
        abort();
    }
    printf("\nSender: Acquiration Done.\n");


    int msid1, msid2, i = 0;
    printf("\nOpening Message Queue with k1 ...: ");
    if ((msid1 = msgget(k1, 0666 | IPC_CREAT))< 0)
    {
        perror("Failed");
        abort();
    }
    printf("Done\n");



    if ((msid2 = msgget(k2, 0666 | IPC_CREAT)) < 0)
    {
        perror("Message Queue Recieve\n");
        exit(1);
    }
    printf("Done\n");


    for(;i < 50;i = idBuffer.id[0] + 1)
    {

        printf("\nSender: Storing following Strings in Packet");

        message.messageType = 1;

        int j =i;
        while(j<i+5)
        {
            strcpy(message.store[(j - i) % 5].info, arr[j]);
            message.store[(j - i) % 5].id = j;
            printf("\nString: %s, Id : %d ", arr[j], j);
            j++;
        }


        printf("\n\nMSending Packet... msg queue ");
        msgsnd(msid1, &message, sizeof(message), 0);
        
        printf("\nPacket Sent of sender\n");
        
        sleep(5);

        msgrcv(msid2, &idBuffer, sizeof(idBuffer), 2, 0);

        printf("\n ID: %d \n", idBuffer.id[0]);
       
    }


    printf("closing  k2 queue message \n");

    msgctl(msid2,IPC_RMID,NULL);

    return 0;
}