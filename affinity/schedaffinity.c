
// The following Code is a demonstration purpose of Priority Inversion During V&V CEP 9/07/12
// Most of the code is written intentional to only demonstrate the purpose , don't try to use as it is
// Author V&V Team



#include <stdio.h>
#include <sched.h>

double busy_loop(long n)
{

    double res = 0;
    long i = 0;
    while (i <n * 200000) {
        i++;
        res += i * i;
	res = res/i;
    }
    return res;
}

int main(int argc, char *argv[])
{

    unsigned long mask = 1;

#ifdef BINDCPU 
    mask = atoi(argv[1]);
    printf("Process Binded on CPU %d \n",mask);
    if (sched_setaffinity(getpid(), sizeof(mask), &mask) <0) {
        perror("sched_setaffinity");
    }
#endif 
   while(1) 
	busy_loop(2000);
}
