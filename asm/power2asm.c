#include <stdio.h>
#include <time.h>

long mult(int value1, int value2);

int main(int argc,char *argv[])
{	int n,biton=0;
	int number;


	n = atoi(argv[1]);	
//	if((n&(-n)) == n) {

	for(number=1;number<=n;++number) { 
		
		asm("bsrl %1,%0" : "=r" (biton) : "r" (n)); 
	}
		printf("Number is Power of 2 and BIT is set at %d for %d \n",biton,n);


//	}

	return 0;
}
