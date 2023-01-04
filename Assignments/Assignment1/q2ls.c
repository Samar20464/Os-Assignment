#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *Ls()
{
    printf("Enter the command\n");
    printf("1. For -a to show hidden files\n");
    printf("2. for -l  list files and directories");
    printf("\n");
    int choice;
    scanf("%d",&choice);
    switch (choice)
    {
        case 1:
            system("ls -a");
        break;
        case 2:
            system("ls -l");
        break;
        default:
            printf("Invalid Commads");
        break;
    }
}


int main()
{
    pthread_t pid;
    pthread_create(&pid,NULL,&Ls,NULL);
    pthread_join(pid, NULL);
  
    printf("\nThread is terminated\n");

    pthread_exit(NULL);
}