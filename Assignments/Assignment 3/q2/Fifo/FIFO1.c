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


void RandomString(int no, char *res)
{

    char alphab[26] = "abcdefghijklmnopqrstuvwxyz",dig[2];
    int i =0;
    while(i< no)
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

    printf("\n Sender creating");
    if(mkfifo(name1,0777) < 0)
    {
        perror(" Failed");
        abort();
    }
    
    int f1,f2;
    printf("\nCreated successful");

    printf("\nOpening Sender\n");
    printf("\nWaiting for Reciever to Open \n");
    if ((f1 = open(name1, O_WRONLY ))  < 0)
    {
        perror(" Failed");
        abort();
    }    

    printf("\nOpening Reciever\n");
    if ((f2 = open(name2, O_RDONLY)) < 0)
    {
        perror(" Failed");
        abort();
    }

    int i =0;

    int l;
    for(;i<50;i = l+1)
    {
        int j = i;
        while (j< i+5)
        {
            strcpy(info[(j - i) % 5].information, arr[j]);
            info[(j - i) % 5].id = j;
            printf("\nString: %s, Id : %d ", arr[j], j);
            j++;
        }
        
        ssize_t len;
        int l2;
        if((len = write(f1,&l,sizeof(l2))) < 0)
        {
         perror(" Failed f1");
        abort();
        }

        if((len = write(f2,&l,sizeof(l2))) < 0)
        {
         perror(" Failed f2");
        abort();
        }

        printf("\nRecieved ID: %d \n", l);

        printf("\nFeeding Recieved Id...\n"); 

        i = l + 1;
    }
    
    close(f1);
    close(f2);
}