#include <unistd.h>
#include <stdio.h>


#define  NUM_LINES_PRINT  25
main()
{
    pid_t pro_id;
    int i;

    printf("FORK_WITH_EXEC:before fork (father pid=%d)\n", getpid());
    pro_id=fork();
    if(pro_id==0) // Child process
    {
       char *args[] = {NULL};
       execvp("./simple_fork", args);
       printf("FORK_WITH_EXEC:Hello world from child  (pid=%d)\n", getpid());
    }
    else if(pro_id > 0) // parent process
    {
        printf("FORK_WITH_EXEC:Hello world from parent  (pid=%d)\n",  getpid());
    }

    while(1)
    {
      printf("FORK_WITH_EXEC: endless loop !!!! \n");
      sleep(3);
    }
}
