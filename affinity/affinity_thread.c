
#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>

// The following Code is a demonstration purpose of Priority Inversion During V&V CEP 9/07/12
// Most of the code is written intentional to only demonstrate the purpose , don't try to use as it is
// Author V&V Team



double busy_loop(long n)
{

    double res = 0;
    long i = 0;
    while (i <n * 6000000) {
        i++;
        res += i * i;
	res = res/i+2;
    }
    return res;
}

void *thread_task1(void *param)
{
    // Mask Was a Bitmap Don't Worry
    unsigned long mask = 1; 

    pthread_setname_np(pthread_self(),"BusyTask");


    // Schedule on Core1 Now 
    while(1) {  
    mask = 1;
    printf("Switching to CPU 1 Now \n");
    if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) <0) {
        perror("pthread_setaffinity_np");
    }

    printf("result: %f\n", busy_loop(100));

    printf("Switching to CPU 2 Now \n");
    mask = 2;   //Schedule on Core 2 Now 
    if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) <0) {
        perror("pthread_setaffinity_np");
    }
    printf("result: %f\n", busy_loop(100));


    printf("Switching to CPU 3 Now \n");
    mask = 4;   //Schedule on Core 3 Now 
    if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) <0) {
        perror("pthread_setaffinity_np");
    }
    printf("result: %f\n", busy_loop(100));
  

    printf("Switching to CPU 4 Now \n");
    mask = 8;   //Schedule on Core 3 Now 
    if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) <0) {
        perror("pthread_setaffinity_np");
    }
    	printf("result: %f\n", busy_loop(100));
    }


}


int main(int argc, char *argv[])
{

    pthread_t task1,task2;

    if (pthread_create(&task1, NULL, thread_task1, NULL) != 0) {
        perror("pthread_create");
    }

    pthread_join(task1,NULL);
}
