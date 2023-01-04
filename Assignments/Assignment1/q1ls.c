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
    char *directory = (char *)malloc(sizeof(directory));
    int command;
    if(pid == -1)
    {
        perror("fork Error");
        abort();
    }
    else if(pid ==0)
    {
        printf("\nEnter directory: ");
		scanf("%s",directory);
        printf("Enter command\n 1. to show hidden files \n2. for  list files and directories\n");
        scanf("%d",&command);
        switch(command)
        {
            case 1:
                execl("/bin/ls","ls","-","a",directory,NULL);
            break;
            case 2:
                execl("/bin/ls","ls","-","l",directory,NULL);
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