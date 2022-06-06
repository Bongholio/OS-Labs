#include<stdio.h>
#include<signal.h>
#include<unistd.h>


void sig_handler(int signo)
{
  // signal(SIGUSR1, sig_handler);        /*  reset signal (required on some systems)  */
  if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
  else if (signo == SIGINT)
    printf("received SIGINT\n");
}

int main(void)
{
   // use:   kill -USR1  PID        to send SIGNAL from  command line
   if (signal(SIGUSR1, sig_handler) == SIG_ERR)  printf("\ncan't catch SIGUSR1\n");

   //  Set a  handler for Ctrl+C 
   if (signal(SIGINT, sig_handler) == SIG_ERR)   printf("\ncan't catch SIGINT\n");
  
   while(1) 
   	sleep(1);

   return 0;
}
