#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void *RM()
{
    printf("Enter the command\n");
    printf("1.TO delete this file or not(with precaution)\n");
    printf("2 To delete this file without preacaution.");
    printf("\n");
    int choice;
    char command1[100] = "rm -i ";
    char command2[100] = "rm ";
    char file[100];
    scanf("%d",&choice);
    switch (choice)
    {
        case 1:
            printf("Enter file name\n");
            scanf("%s",file);
            strcat(command1,file);
            system(command1);
        break;
        case 2:
            printf("Enter file name\n");
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
    pthread_create(&pid,NULL,&RM,NULL);
    pthread_join(pid, NULL);
  
    printf("\nThread is terminated\n");

    pthread_exit(NULL);
}