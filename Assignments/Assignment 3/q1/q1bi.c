#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t forks[5],Bowls[2];

void * philophers(void *args)
{

    int ids= *(int*) args;
    int run =1;
    while(run)
    {

        if(ids%2!=0)
        {
            sem_wait(&forks[(ids + 1) % 5]);
			sem_wait(&forks[ids]);
        }
        else
        {
            sem_wait(&forks[ids]);
			sem_wait(&forks[(ids + 1) % 5]);
        }

        sem_wait(&Bowls[ids%2]);

		printf("This Philosopher is  %d and is eating\n", ids);
		
		sem_post(&Bowls[ids%2]);
		sem_post(&forks[ids]);
		sem_post(&forks[(ids + 1) % 5]);

    }

}

int main()
{
   
    pthread_t Create[5];
    int args[5];
    for(int count=0;count<5;count++)
    {  
        sem_init(&forks[count],0,1);
    }

    for(int count=0;count<2;count++)
    {  
        sem_init(&Bowls[count],0,1);
    }

    for (int i = 0; i < 5; i++) {
        args[i] = i;
	}

    pthread_create(&Create[0], NULL, philophers, &args[0]);
    pthread_create(&Create[1], NULL, philophers, &args[1]);
    pthread_create(&Create[2], NULL, philophers, &args[2]);
    pthread_create(&Create[3], NULL, philophers, &args[3]);
    pthread_create(&Create[4], NULL, philophers, &args[4]);
	
    pthread_join(Create[0], NULL);
    pthread_join(Create[1], NULL);
    pthread_join(Create[2], NULL);
    pthread_join(Create[3], NULL);
    pthread_join(Create[4], NULL);
}