// Trace Output with command  ==> ps -Leo pid,tid,class,sched,rtprio,s,comm 


// The following Code is a demonstration purpose of Priority Inversion During V&V CEP 9/07/12
// Most of the code is written intentional to only demonstrate the purpose , don't try to use as it is 
// Author V&V Team

#define _GNU_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>

#define SUCCESS 0
#define FAIL -1 
#define SCHED_POLICY SCHED_RR

#define NTHREADS 2 
#define MAX_PRIORITY 98
#define USE_CORE 8


pthread_mutex_t my_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_t lpTask,mpTask[NTHREADS],hpTask;

int timerCount;
int watchTimer;


void setThreadName(const char *rname) {

	unsigned long mask=USE_CORE;
	pthread_t current_threadID=0;

	char name[32]="\0";
	strcpy(name,rname);
	current_threadID=pthread_self();
	pthread_setname_np(current_threadID,name);
	if (pthread_setaffinity_np(current_threadID, sizeof(mask), &mask) <0) {
        	perror("pthread_setaffinity_np");
		exit(FAIL);
	}

}

double do_nothing(long n)
{

    double res = 0;
    long i = 0;
    while (i <n * 600000) {
        i++;
        res += i * i;
	res = res/i;
	usleep(10);
	
    }
    return res;
}



int getThreadPriority() {
	struct sched_param param;
	int policy;


	pthread_getschedparam (pthread_self(), &policy, &param);
	return(param.sched_priority);
	

}

void watchDogTimer() {


	printf("Check Whether High Priority Process Completed its Task \n");
	if(watchTimer > timerCount)  {
		printf("Health of High Priority Process Dead Go For Reset Now...!  watchTimer = %d and timerCount = %d \n",watchTimer,timerCount);

		pthread_setschedprio(lpTask,MAX_PRIORITY);
	}
	watchTimer++;
	alarm(5);
}


void *lowPriorityTask(void *null) {

	int newPriority=0; 
	setThreadName("LowPriorityTask");

	while(1) {
	        printf("lowPriorityTask Scheduled => Priority = %d \n",getThreadPriority());
	        pthread_mutex_lock(&my_mutex);

	        printf("Entered Low Priority Critical Section ....! Timer Count = %d \n",timerCount); 
		if(timerCount % 4 == 0) {	
			while(1) {
				newPriority=getThreadPriority();
	  	        	if(newPriority != 1) {
                                	 printf("Thread Priority Raised From 1  to %d \n",newPriority);
					 sleep(2);
					 exit(FAIL);
				}
				
				usleep(100000);
                      	}
			
			usleep(100000);
			
		}
                pthread_mutex_unlock(&my_mutex);
		printf("Out Of  Low Priority Critical Section ....! \n\n"); 
		sched_yield();
	}
        printf("Done With Low Priority Task  ....! \n");
        pthread_exit(NULL); 
}



void *mediumPriorityTask(void *null)
{


	setThreadName("MedPriorityTask");


	printf("Medium PriorityTask Scheduled => Priority = %d \n",getThreadPriority());
	while(1) {
		asm("nop");
		do_nothing(9999344);
		do_nothing(9999344);
		do_nothing(9999344);
	}
        printf("Done With Medium Priority Task  ....! \n");
        pthread_exit(NULL);
}


void *highPriorityTask(void *null) {

	setThreadName("HigPriorityTask");
        while(1) {

		printf("\n\nHigh PriorityTask Scheduled => Priority = %d \n",getThreadPriority());
                printf("Checking for Mutex...! Holded with Low Priority  \n");
                pthread_mutex_lock(&my_mutex);
			
                        printf("Entered high Priority Critical Section ....! \n");
			watchTimer = 0;
			timerCount++;
                        printf("===> Out Of  high Priority Critical Section ....! \n\n");
			do_nothing(213);

                pthread_mutex_unlock(&my_mutex);	

        }
        printf("\n\n ====>  Done With high Priority Task  ....! \n");
        pthread_exit(NULL);
}

int main() {

	struct sched_param threadPriority;
	pthread_attr_t set_attr,get_attr;	
	pthread_mutexattr_t inh_protocol;
	long no_of_cpus; 
	int current_policy=-1,i; 

	signal(SIGALRM,watchDogTimer);
	alarm(5);
	

//	setThreadName("Main_ParentTask");

	// Find the Number OF Cores in CPU  and The MaX , Min Priorities for each Scheduling Policy. 
	no_of_cpus = sysconf(_SC_NPROCESSORS_CONF);
	printf("Number of CPUS Configured == %ld \n",no_of_cpus);
	printf("SCHED_RR = %d , SCHED_FIFO = %d , SCHED_OTHER = %d \n",SCHED_RR,SCHED_FIFO,SCHED_OTHER);
	printf("SCHED_RR MAX = %d , SCHED_RR MIN = %d \n", sched_get_priority_max(SCHED_RR),sched_get_priority_min(SCHED_RR));
	printf("SCHED_FIFO MAX = %d SCHED_FIFO MIN = %d \n",sched_get_priority_max(SCHED_FIFO),sched_get_priority_min(SCHED_FIFO)); 
	printf("Tyring with Policy = %d \n",SCHED_POLICY);
	

	// Initialize attributes  and request EXPLICIT SCheduling to Set the Attributes
	pthread_attr_init(&set_attr);
	if((pthread_mutexattr_init(&inh_protocol)) != SUCCESS)  {

		printf("Unable to SET MUTEX ATTR \n");
		exit(FAIL);
	}

	if((pthread_mutexattr_settype(&inh_protocol, PTHREAD_MUTEX_ERRORCHECK)) != SUCCESS) {
		printf("SET TYPE Failed ...! \n");
		exit(FAIL);
	}
	if((pthread_mutexattr_setprotocol(&inh_protocol,PTHREAD_PRIO_INHERIT)) != SUCCESS) {
		printf("Unable to SET PRIORITY INHERITANCE \n");
		exit(FAIL);

	}
	if((pthread_mutex_init(&my_mutex,&inh_protocol)) != SUCCESS) {
		printf("Unable to INIT Mutex \n");
		exit(FAIL);
	}

	int getprotocol = -1;
	if((pthread_mutexattr_getprotocol(&inh_protocol,&getprotocol)) != SUCCESS) {
		printf("Unable to Get Protocol \n");
		exit(0);
	}
	printf("Protocol == %d \n",getprotocol);
	
	pthread_attr_setinheritsched(&set_attr,PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setdetachstate(&set_attr,PTHREAD_CREATE_JOINABLE);
	pthread_attr_getschedpolicy(&set_attr,&current_policy);	
	
	printf("Current Policy = %d \n",current_policy);  

	// Set the Sceduling Policy and Priority Now for Low ;
	threadPriority.sched_priority = sched_get_priority_min(SCHED_POLICY);
	pthread_attr_setschedpolicy(&set_attr,SCHED_POLICY);
	pthread_attr_setschedparam(&set_attr,&threadPriority); 
	pthread_create(&lpTask,&set_attr,lowPriorityTask,NULL);

	printf("Low Priority Created ...\n");

		

        // Set the Sceduling Policy and Priority Now for Medium ;
	for(i =0;i<NTHREADS;i++) {
        threadPriority.sched_priority = sched_get_priority_max(SCHED_POLICY)-50;
        pthread_attr_setschedpolicy(&set_attr,SCHED_POLICY);
        pthread_attr_setschedparam(&set_attr,&threadPriority); 
	pthread_create(&mpTask[i],&set_attr,mediumPriorityTask,NULL);
	}

	printf("Medium  Priority Created ...\n");

        // Set the Sceduling Policy and Priority Now for High ;
        threadPriority.sched_priority = sched_get_priority_max(SCHED_POLICY)-1;
        pthread_attr_setschedpolicy(&set_attr,SCHED_POLICY);
        pthread_attr_setschedparam(&set_attr,&threadPriority); 
	pthread_create(&hpTask,&set_attr,highPriorityTask,NULL);

	printf("High Priority Created ... \n");



	// Wait Till All Threads were completed...! 
	pthread_join(lpTask,NULL);
	for(i=0;i<NTHREADS;i++)
	pthread_join(mpTask[i],NULL);
	pthread_join(hpTask,NULL); 
	return(0);
}
