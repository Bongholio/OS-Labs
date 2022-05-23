#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MaxItems   10      // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5      // Size of the buffer

#define NUM_PRODUCERS_CONSUMERS 1            // max is 10


int in = 0;         	  	// index to put a new item
int out = 0;          		// index to get the next item
int buffer[BufferSize];

void *producer(void *pno)
{   
    int item;
    int i;

    for(i = 0; i < MaxItems; i++) {
        item = i + 1;
 
        if( buffer[in] != -1)
	{
		printf("producer: ERROR  overiding  not consumed item !!!! \n");
		exit(0);
	}     

        buffer[in] = item;
        printf("Producer %d: Insert Item %d at index  %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;

        usleep(1000000); 
    }
}
void *consumer(void *cno)
{   
    int i;

    for(i = 0; i < MaxItems; i++) {

        int item = buffer[out];
        buffer[out] = -1;                // mark as empty
        printf("Consumer %d: Remove Item %d from index %d\n",*((int *)cno),item, out);
        if( item  == -1)
        {
                printf("consumer: ERROR  consuming not existing item !!!! \n");
                exit(0);
        }
        

        out = (out+1)%BufferSize;
    }
}

int main()
{   
    int i;

    srand(time(0));            // set seed for RAND()
    pthread_t pro[NUM_PRODUCERS_CONSUMERS],con[NUM_PRODUCERS_CONSUMERS];


    int a[NUM_PRODUCERS_CONSUMERS];     //Just used for numbering the producer and consumer

    for ( i = 0; i < NUM_PRODUCERS_CONSUMERS; i++)
    	a[i] = i+1;

    for ( i = 0; i < BufferSize; i++)
        buffer[i] = -1;

     for( i = 0; i < NUM_PRODUCERS_CONSUMERS; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }

    for( i = 0; i < NUM_PRODUCERS_CONSUMERS; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(i = 0; i < NUM_PRODUCERS_CONSUMERS; i++) {
        pthread_join(pro[i], NULL);
    }

    for(i = 0; i < NUM_PRODUCERS_CONSUMERS; i++) {
        pthread_join(con[i], NULL);
    }

    return 0;
    
}
