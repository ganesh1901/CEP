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
#include <fcntl.h>
#include <assert.h>


// Compile with -DNDEBUG to remove assertions

#define SUCCESS 0
#define FAIL -1 

typedef struct {

	char *strPtr;
        FILE *fp;	
}globalInputs;

 
globalInputs inputStruct;


void cleanMemory() {
	printf("clean memory called ... \n");	
	free(inputStruct.strPtr);

}

void cleanFilePointers() {
	printf("clean file pointers called ... \n"); 
	fclose(inputStruct.fp);
}

void cleanall_IPCS() {     // Clean all Shared resources semaphores, shared memories etc.

}



int main(int argc,char *argv[]) {

	atexit(cleanFilePointers);
	atexit(cleanMemory); 
	
	assert(argc != 1);
	inputStruct.strPtr = (char *) malloc(sizeof(char)*64);
	assert(inputStruct.strPtr != NULL);
	
	inputStruct.fp = fopen(argv[1],"w+");
        assert(inputStruct.fp != NULL);

	strcpy(inputStruct.strPtr,"Hello World...!");
	fprintf(inputStruct.fp,"%s",inputStruct.strPtr);
	return(0);
}
