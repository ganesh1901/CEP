#include <stdio.h>
#include <time.h>

long mult(int value1, int value2);

int main(int argc,char *argv[])
{	int n,biton=-1,x,number,i;
	clock_t start, finish;
	n = atoi(argv[1]);
	x = n;

	
	for(number=1; number <= n; ++number) {
	for(i=(number>>1),biton=0; i!=0; ++biton) {
		i >>= 1;	 
	}
	}

		
		
	printf("Number is Power of 2 and BIT is set at %d for %d \n",biton,x);



	return 0;
}
