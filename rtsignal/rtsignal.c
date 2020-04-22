#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <mqueue.h>
#include <fcntl.h>              /* For definition of O_NONBLOCK */



#define HANDLE_HIGH SIGRTMIN
#define HANDLE_LOW SIGINT


static int rt_index=0;
char rt_msg[10][64]={"Blow Emergency Alarm,Open Emergency Plans","Shut All the Valves","Close and Power Down all the reactors"};


static void sig_handler(int sig_no)
{
	if(sig_no == HANDLE_HIGH) {
		printf("High Priority Signal Received %d Time \n",rt_index+1);	
		printf("Message = [%s] \n\n",rt_msg[rt_index]);
		rt_index++;
	} 

	if(sig_no == HANDLE_LOW) {

		printf("Low Priority Signal Received %d Time \n",rt_index+1);	
		printf("Message = [%s] \n\n",rt_msg[rt_index]);
		rt_index++;
	}
	

	
}

int main()
{
    struct sigevent sev;
    sigset_t newMask,oldMask;
    struct sigaction sa;

	
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sig_handler;
    if (sigaction(HANDLE_HIGH, &sa, NULL) == -1)
        perror("sigaction");

    if (sigaction(HANDLE_LOW, &sa, NULL) == -1)
        perror("sigaction");

    /* Block the notification signal and establish a handler for it */

   sigemptyset(&newMask);                      // Exclude all signals  
   sigaddset(&newMask, HANDLE_HIGH);           // Add the required set
   sigaddset(&newMask, HANDLE_LOW);


    // Block the signal Delivery now as i am entering critical section
    if (sigprocmask(SIG_BLOCK, &newMask, &oldMask) == -1) {
	printf("Uanble to Set sigprocmask \n");
	exit(0);

    } 	



    printf("Entering Critical Section ...! \n");
    getchar();	
    printf("Out of   Critical Section ...! \n\n");

    //Restore Old Set and Service all the signals that happened during critical section  
    if (sigprocmask(SIG_SETMASK, &oldMask, NULL) == -1) {
	printf("Uanble to Set sigprocmask \n");
	exit(0);

     } 

}
