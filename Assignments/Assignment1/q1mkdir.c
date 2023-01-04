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
    char *file =  (char *)malloc(sizeof(file));
    int command;
    if(pid == -1)
    {
        perror("fork Error");
        abort();
    }
    else if(pid ==0)
    {
        printf("Enter command\n");
        printf("1. Create directories and displays a message for every directory created.  \n");
        printf("2 If any directories dosn't exit then with -p command will create those directories.\n");
        scanf("%d",&command);
        switch(command)
        {
            case 1:
                printf("Enter file name ");
                scanf("%s",file);
                execl("/usr/bin/mkdir","mkdir","-v",file,NULL);
            break;
            case 2:
                printf("Enter file name ");
                scanf("%s",file);
                execl("/usr/bin/mkdir","mkdir","-p",file,NULL);
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