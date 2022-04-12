#include <unistd.h>
#include <stdio.h>


int main()
{
    pid_t pro_id;
    int i;

    printf("SIMPLE_FORK:before fork (father pid=%d)\n", getpid());
    pro_id=fork();
    if(pro_id==0) // Child process
    {
        printf("SIMPLE_FORK: Hello world from child %d (pid=%d)\n",i, getpid());
    }
    else if(pro_id > 0) // parent process
    {
        printf("SIMPLE_FORK: Hello world from parent %d (pid=%d)\n", i, getpid());
    }
    else
       printf("fork failure\n");

    printf("PRES any CHAR to  continue... \n");
    getchar();
    printf("After  getting  CHAR  ... (%s) \n",  (pro_id == 0) ? "child":"father");
    return(0);
}


