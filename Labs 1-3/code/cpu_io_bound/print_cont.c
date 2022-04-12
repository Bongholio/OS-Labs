#include <unistd.h>
#include <stdio.h>


#define  NUM_LINES_PRINT  25
main()
{
    pid_t proc_id = getpid();
    int i;

	while(1)
	{
	
       for( i=0; i<NUM_LINES_PRINT;i++)
          printf("Hello world from PID=%d\n",proc_id);

	}
}


