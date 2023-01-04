#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>


#define name1 "fifo1"
#define name2 "fifo2"

struct contains
{
    int id;
    char information[50];
}info[5];


int main()
{

    printf("\n Reciever fifo");
    if(mkfifo(name1 ,0777) < 0){
        perror(" Failed");
        abort();
    }
    printf("\n Creation Done.\n");

    int f1, f2;

    

    printf("\nOpening Reciever fifo\n");
    if ((f1 = open(name1, O_RDONLY )) == -1)
    {
        perror(" Failed");
        abort();
    }
    int i = 0;
    int till = -1;

    sleep(5);

    printf("\nOpening Sender fifo\n");
    if ((f2 = open(name2, O_WRONLY)) < 0)
    {
        perror(" Failed");
        abort();
    }

    while (till < 49)
    {


        printf("\nRecieving");

    
        read(f1,info, sizeof(info));
        int j =0;
        while(j< 5)
        {
             if (info[j].id == till + 1)
            {
                till = info[j].id;
                printf("\nString is : %s, and id is  : %d",info[j].information,info[j].id);
            }
            else
                break;
            j++;
        }
        printf("\nRecieved.\n");

        printf("\nRecieved ID: %d\n", till);

        sleep(5);


        size_t length;
        printf("\nSending back Highest most ID...");
        if ((length = write(f2, &till, sizeof(till))) < 0){
            perror(" Failed");
            abort();
        }
     
    }

    printf("\nData Recieved Succesfully\n\n");

    close(f1);
    close(f2);
    return 0;
}


