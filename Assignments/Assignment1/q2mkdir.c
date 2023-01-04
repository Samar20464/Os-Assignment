#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void *MKDIR()
{
    printf("Enter the command\n");
    printf("1.Create directories and displays a message for every directory created.\n");
    printf("2 If any directories dosn't exit then with -p command will create those directories.");
    printf("\n");
    int choice;
    char command1[100] = "mkdir -v ";
    char command2[100] = "mkdir -p ";
    char file[100];
    scanf("%d",&choice);
    switch (choice)
    {
        case 1:
            printf("Enter Directory name\n");
            scanf("%s",file);
            strcat(command1,file);
            system(command1);
        break;
        case 2:
            printf("Enter Directory name\n");
            scanf("%s",file);
            strcat(command2,file);
            system(command2);
        break;
        default:
            printf("Invalid Commads");
        break;
    }
}


int main()
{
    pthread_t pid;
    pthread_create(&pid,NULL,&MKDIR,NULL);
    pthread_join(pid, NULL);
  
    printf("\nThread is terminated\n");

    pthread_exit(NULL);
}