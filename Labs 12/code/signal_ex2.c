// C program to implement sighup(), sigint()
// and sigquit() signal functions
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
  
// function declaration
void sighup();
void sigint();


int got_sighup_flag = 0;
int got_sigint_flag = 0;


void parent_code( int pid)
{

   /* pid hold id of child */
    printf("\nPARENT: sending SIGHUP to child \n\n");
    kill(pid, SIGHUP);

    sleep(2); /* pause for 2 secs */
    printf("\nPARENT: sending SIGINT to child \n\n");
    kill(pid, SIGINT);

}

void child_code()
{
   // get ready for  the 2 SIGNALs
   signal(SIGHUP, sighup);
   signal(SIGINT, sigint);

   while ( !got_sighup_flag || !got_sigint_flag);
   
   printf("\nCHILD: finished !!! \n");

}

  
// driver code
void main()
{
    int pid;
  
    /* get child process */
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
  
    if (pid == 0) { /* child */
		child_code();
    }
    else /* parent */
    { 
		parent_code(pid);
    }
}


  
// sighup() function definition
void sighup()
  
{
    signal(SIGHUP, sighup); /* reset signal */
    printf("CHILD: I have received a SIGHUP\n");
    got_sighup_flag = 1;
}
  
// sigint() function definition
void sigint()
  
{
    signal(SIGINT, sigint); /* reset signal */
    printf("CHILD: I have received a SIGINT\n");
    got_sigint_flag = 1;
}
  
