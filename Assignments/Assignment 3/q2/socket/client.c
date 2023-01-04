#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#define q1C "socket"
struct contains
{
    int id;
    char information[50];
};

int main()
{
   

    printf("\nCreating Client\n");

    register int _server, len;
    struct sockaddr_un behav;
    if ((_server = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("Failed\n\n");
        abort();
    }

    printf("Client Created\n");

    char *arr[50];
    behav.sun_family = AF_UNIX;
    strcpy(behav.sun_path, q1C);
    int log = -1;
    len = sizeof(behav.sun_family) + strlen(behav.sun_path);

    printf("Creating\n");
    if (connect(_server, (struct sockaddr *)&behav, len) < 0) 
    {
        perror("Failed");
        exit(EXIT_FAILURE);
    }
    printf("Sucessful\n");
    int i =0;
    while (i< 50)
    {
        struct contains info[5];

        printf("\nRecieving");
        
        if(read(_server,info,sizeof(info)) < 0)
        {
            perror("Failed");
            abort();
        }

        int j =0;
        while(j<5)
        {
            if (info[j].id == i + 1)
            {
                i = info[j].id;
                printf("\nString is : %s, and id is  : %d",info[j].information ,info[j].id);
            }
            else
                break;

            j++;
        }
        

        printf("\nPacket Recieved.\n");

        printf("\n most ID: %d\n", i);

        sleep(5);

        size_t length;
        printf("\nSending back Highest most ID...");       
        if ((length = send(_server, &i, sizeof(log), i)) < 0){
           perror("Failed");
            abort();
        }

        printf("\nFeedback ID Sent.\n");

    }   

    close(_server);
}