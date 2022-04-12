#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define  NUM_LINES_PRINT 1 
main()
{
    pid_t pro_id;
    int i, j;
    char tmp_str[50];

    printf("before fork\n");
    pro_id=fork();
    if(pro_id==0) // Child process
    {
       for( i=0; i<NUM_LINES_PRINT;i++)
       {	  
             sprintf(tmp_str, "Hello world from child %d\n",i);
             for(j=0; j<strlen(tmp_str); j++)
	     {
                printf("%c", tmp_str[j] );    
                fflush(stdout);
	     }
         printf("\n");    
       }
    }
    else if(pro_id > 0) // parent process
    {
       for( i=0; i<NUM_LINES_PRINT;i++)
       {
             sprintf(tmp_str, "Hello world from parent %d\n",i);
             for(j=0; j<strlen(tmp_str); j++)
             {
                printf("%c", tmp_str[j] );
                fflush(stdout);
             }
         printf("\n");
       }
    }
    else
       printf("fork failure\n");
}


