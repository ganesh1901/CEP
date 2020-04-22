#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


int check (char *test) {

	if(strcmp(test,"PASS") == 0) 
		return 0;
	return 1; 
}


int main(int argc, char *argv[]) {

	int retVal=-1;
/*
	if(argc < 2) {
		printf("Invalid Arguments ....! \n");
		exit(0);
	} */

	retVal = check(argv[1]);

	printf("Return Value from check = %d | ARG1 = %s \n",retVal,argv[1]);

	if(retVal == 0) { 
		printf("Passed Authentication Test...!,Continue to execute \n");
		return(0);
	}
        else  {
		printf("Failed Authentication Test, Program Aborted....!\n");
		return(1);
	}

	getchar();

}	
