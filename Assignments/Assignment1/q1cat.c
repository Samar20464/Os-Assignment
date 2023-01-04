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
    char *path =  (char *)malloc(sizeof(path));
    char *desti =  (char *)malloc(sizeof(desti));
    char *cmm = ">";
    int command;
    if(pid == -1)
    {
        perror("fork Error");
        abort();
    }
    else if(pid ==0)
    {
        printf("Enter the command\n");
        printf("1. To show content of filename.\n");
        printf("2  To view file with line noes\n");
        printf("\n");
        scanf("%d",&command);
        switch(command)
        {
            case 1:
                printf("Enter file name ");
                scanf("%s",path);
                execl("/bin/cat","cat",path,NULL);
            break;
            case 2:
                printf("Enter file name ");
                scanf("%s",desti);
                execl("/usr/bin/cat","cat","-n",desti,NULL);
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