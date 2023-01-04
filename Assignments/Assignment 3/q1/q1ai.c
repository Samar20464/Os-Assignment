#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <pthread.h>

struct Semaaphore
{
    ssize_t count;
    pthread_mutex_t lock;
    pthread_cond_t var;
} *Forki;

void my_Semaaphore_init(struct Semaaphore *Semaa, int number)
{
    if(Semaa == NULL)
        return ;
    Semaa->count = number;
    pthread_mutex_init(&Semaa->lock, NULL);
    pthread_cond_init(&Semaa->var, NULL);
}

void signal(struct Semaaphore *Sema)
{
    if(Sema == NULL)
        return ;
    int result =  pthread_mutex_lock(&Sema->lock);
    if(result<0)
    {
        perror("pthread is lock");
    }
    Sema->count++;
    if (Sema->count == 1)
    {
        pthread_cond_signal(&Sema->var);
    }
    result =pthread_mutex_unlock(&Sema->lock);
    if(result<0)
    {
        perror("pthread is lock");
    }
}

void wait(struct Semaaphore *Sema)
{
    if(Sema == NULL)
        return ;
    
    int result =  pthread_mutex_lock(&Sema->lock);
    if(result<0)
    {
        perror("Try unlock pthread_mutex_unlock");
    }
    if (Sema->count == 0)
    {
        pthread_cond_wait(&Sema->var, &Sema->lock);
    }
    Sema->count--;
    pthread_mutex_unlock(&Sema->lock);
}
 
int number;

void *philosDinner(void *arg)
{
    int count = *(int *)arg;
    int run =1;
    while (run)
    {
        //strict ordering of resource
        printf("This Philospher  %d and is  ready to eat.\n", count);
       
       if (count % 2 != 0)
        {
            wait(&Forki[(count + 1) % number]);
            wait(&Forki[count]);
        }
        else
        {
            wait(&Forki[count]);
            wait(&Forki[(count + 1) % number]);
            
        }
        printf("This Philospher number is  %d and  currently eating using Forkis which is  %d and %d. \n", count, (count + 1) % number, count);
        printf("Finally this Philospher has  %d  done eating. \n\n", count);
        sleep(2);

        if (count % 2 != 0)
        {
            signal(&Forki[count]);
            signal(&Forki[(count + 1) % number]);
        }
        else
        {
            signal(&Forki[(count + 1) % number]);
            signal(&Forki[count]);
        }
    }
}

void main()
{
    number = 5;
    pthread_t philos[5];
    int args[5];

    Forki = (struct Semaaphore *)malloc(sizeof(struct Semaaphore) * number);
    


    for (int i = 0; i < number; i++)
    {
        my_Semaaphore_init(&Forki[i], 1);
    }

    for (int i = 0; i < 5; i++) {
        args[i] = i;
	}
    pthread_create(&philos[0], NULL, philosDinner, &args[0]);
    pthread_create(&philos[1], NULL, philosDinner, &args[1]);
    pthread_create(&philos[2], NULL, philosDinner, &args[2]);
    pthread_create(&philos[3], NULL, philosDinner, &args[3]);
    pthread_create(&philos[4], NULL, philosDinner, &args[4]);

    pthread_join(philos[0], NULL);
    pthread_join(philos[1], NULL);
    pthread_join(philos[2], NULL);
    pthread_join(philos[3], NULL);
    pthread_join(philos[4], NULL);
    return;
}