#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N  			5
#define NUM_CYCLES              1         // number of times each Phil tries to eay 

sem_t chopstick[N];

void * philos(void *);
void * check_dead_lock(void *);
void eat(int);

int main()
 {
         int i,n[N];
         pthread_t T[N];

         for(i=0;i<N;i++)
         	sem_init(&chopstick[i],0,1);

         for(i=0;i<N;i++){
                 n[i]=i;
                 pthread_create(&T[i],NULL,philos,(void *)&n[i]);
         }

         for(i=0;i<N;i++)
                 pthread_join(T[i],NULL);
 }


void * philos(void * n)
 {
         int ph=*(int *)n;
         int i = 1; 
 
         while (  i <= NUM_CYCLES )
         {

	         printf("Philosopher %d wants to eat: %d  (tries to pick left chopstick)  \n",
                                              ph, i);
	         sem_wait(&chopstick[ph]);      

	         printf("Philosopher %d picked the left chopstick: %d \n",ph, i);

 	         printf("Philosopher %d tries to pick the right chopstick: %d\n", ph, i);
        	 sem_wait(&chopstick[(ph+1)%5]);

        	 printf("Philosopher %d picked  the right chopstick: %d\n",ph, i);

                 printf("Philosopher %d begins to eat: %d\n",ph, i);
                 sleep(2);
                 printf("Philosopher %d has finished eating: %d\n",ph, i);
 
        	 //  release chopsticks
	         sem_post(&chopstick[(ph+1)%5]);
        	 printf("Philosopher %d leaves the right chopstick: %d \n",ph, i);
	         sem_post(&chopstick[ph]);
        	 printf("Philosopher %d leaves the left chopstick: %d\n",ph, i);
              
                 i++;
	}
}

