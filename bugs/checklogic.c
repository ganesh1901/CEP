#include <stdio.h>

int main() {


	int a,b,c,d;

	a=0,b=2,c=2,d=0;

	if(a && b) {
		printf("a && b  = T \n");
	}

	if(c && d)
		printf("c && d  = T \n");

	if(b == c && d) {
		printf("Condition Evaluated \n");
	
	}
	
	

	return(0);
}
