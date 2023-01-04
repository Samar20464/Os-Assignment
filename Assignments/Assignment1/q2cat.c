#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void *MKDIR()
{
    printf("Enter the command\n");
    printf("1. To show content of filename.\n");
    printf("2 For creating new files");
    printf("\n");
    int choice;
    char command1[100] = "cat ";
    char command2[100] = "cat > ";
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
            printf("Invalid Command");
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