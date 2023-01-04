#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *DATE()
{
    printf("Enter the command\n");
    printf("1.To show day name, abbreviated month name, day and GMT\n");
    printf("2. Displays the time in GMT(Greenwich Mean Time)   )");
    printf("\n");
    int choice;
    scanf("%d",&choice);
    switch (choice)
    {
        case 1:
            system("date");
        break;
        case 2:
            system("date -u");
        break;
        default:
            printf("Invalid Commads");
        break;
    }
}


int main()
{
    pthread_t pid;
    pthread_create(&pid,NULL,&DATE,NULL);
    pthread_join(pid, NULL);
  
    printf("\nThread is terminated\n");

    pthread_exit(NULL);
}