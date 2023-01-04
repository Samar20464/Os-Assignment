#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include<sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>
int main(int argc, const char *argv[])
{
    int pid;

    pid = fork();
    int command;
    if(pid == -1)
    {
        perror("fork Error");
        abort();
    }
    else if(pid ==0)
    {
        printf("Enter command\n1. TO show date gmt etc. \n");
    
        printf("2 . Displays the time in GMT(Greenwich Mean Time).\n");
        scanf("%d",&command);
        switch(command)
        {
            case 1:
                execl("/bin/date","date",NULL);
            break;
            case 2:
                execl("/usr/bin/date","date","-u",NULL);
            break;
            default:
                printf("Invalid Command");
        }   
    }
    else
    {
        int status = wait(NULL);
        if(status < 0)
        {
            perror("Child process is not over yet");
            abort();
        }

    }

}