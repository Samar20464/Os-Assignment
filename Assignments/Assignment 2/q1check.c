#define _XOPEN_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> 
#include <time.h>
#include<string.h>
#include<sys/resource.h>
#define BILLION  1000000000L;



const char *sched_policy[] = 
{
    "SCHED_OTHER",
    "SCHED_FIFO",
    "SCHED_RR"
};

struct sched_param defaultProirity = {
        .sched_priority = 5
};




int policy;
pthread_t thread1,thread2,thread3;
pthread_mutex_t m_mtx;
void *countA()
{
    long count;

    while(1)
    printf("in thread 1 ");
    
    for(long i =0;i< (1<<32-1);i++)
        count++;

    
}

void *countB()
{
   
    long count;

    while(1)
    printf("in thread 2 ");
    for(long i =0;i< (1<<32-1);i++)
        count++;
}

void *countC()
{

    long count;

    while(1)
    printf("in thread 3 ");

    for(long i =0;i< (1<<32-1);i++)
        count++;

}

int main()
{
    int thr1 = 1;
    int thr2 = 2;
    int thr3 = 3;



    pthread_create(&thread1,NULL,&countA,&thr1);
    pthread_create(&thread2,NULL,&countB,&thr2);
    pthread_create(&thread3,NULL,&countC,&thr3);
    
    struct sched_param nicePrority;
    nicePrority.sched_priority = nice(0);
    
    pthread_setschedparam(thread1,SCHED_OTHER, &nicePrority);
    pthread_setschedparam(thread2,SCHED_RR,&defaultProirity);
    pthread_setschedparam(thread3,SCHED_FIFO,&defaultProirity);
    
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    exit(EXIT_SUCCESS);
}