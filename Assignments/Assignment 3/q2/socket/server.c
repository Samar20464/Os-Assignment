#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#define size 50
#define Q1 "socket"

struct info
{
    /* information */
    int id;
    char information[10];
}store[5];

void RandomString(int n, char *res)
{

    char alphab[26] = "abcdefghijklmnopqrstuvwxyz", dig[2];
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
    int len2, i = 0;
    struct sockaddr_un behav, fbehav;
    register int con1, server;


    printf("\nCreating Server...");
    if ((con1 = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("acquiration failed");
        exit(1);
    }
    printf("\nSender Server Created\n");

    behav.sun_family = AF_UNIX;
    strcpy(behav.sun_path, Q1);
    unlink(Q1);

    printf("\nBinding \n");
    if (bind(con1, (struct sockaddr *)&behav, sizeof(struct sockaddr_un)) < 0)
    {
        perror("Unsuccessfull");
        abort();
    }
    printf("Binding Successfull...\n");


    printf("\n for listening...\n");
    if (listen(con1, 10) < 0)
    {
        perror("Unsuccessfull");
        abort();
    }

    printf("\nWaiting for Reciever to Conenct...\n");
    if ((server = accept(con1 , (struct sockaddr *)&fbehav, &len2)) < 0)
    {
        perror("Unsuccessfull");
        abort();
    }
    printf("  conected successfully");
    char *arr[50];

    copy(arr);

    int l;
    for(;i<50;i = l+1)
    {
        int j = i;
        while (j< i+5)
        {
            strcpy(store[(j - i) % 5].information, arr[j]);
            store[(j - i) % 5].id = j;
            printf("\nString: %s, Id : %d ", arr[j], j);
            j++;
        }
        
        printf("\n\nServer Sending Packet nowww...");
        send(server, store, sizeof(store), 0);
        printf("\nPacket has been  Sent.\n");


        int l;
        read(server, &l, sizeof(l));

        printf("\nRecieved  %d \n", l);

        i = l + 1;
    }
    close(server);
    return 0;   
}