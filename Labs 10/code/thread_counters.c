
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
  
pthread_t tid[2];


int counter = 0;                 // global counter (shared by the threads)


#define MAX_COUNTER  1000000


  
void* trythis(void* arg)
{
    unsigned long i = 0;


     printf("\n Thread  started\n");

    // for (i = 0; i < (0xFFFFFFFF); i++)   
    for (i = 0; i < MAX_COUNTER; i++)
	counter++;

    return NULL;
}
  
int main(void)
{
    int i = 0;
    int error;
  
    for( i = 0; i <  2; i++) 
    {
        error = pthread_create(&(tid[i]), NULL, &trythis, NULL);

	if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error));
    }
  

    for( i = 0; i <  2; i++)
    	pthread_join(tid[i], NULL);   

    printf("\n Counter is  %d \n", counter);

    return 0;
}
