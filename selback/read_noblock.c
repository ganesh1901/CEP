

// The following Code is a demonstration purpose of Priority Inversion During V&V CEP 9/07/12
// // // Most of the code is written intentional to only demonstrate the purpose , don't try to use as it is
// // // Author V&V Team

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc,char *argv[]) {
	
	int z;	
	int fd;
	char buf[256];
	fd = open("fifo1",O_RDWR|O_NONBLOCK);
	if(fd == -1) {
		printf("Unable to Open File \n");
		perror("Reason: ");
		exit(1);
	}
	while((z=read(fd,buf,sizeof(buf)) <=0));
	if( z >= 0 ) {
        	printf("Number of Characters are ready = %d \n",z);	
		printf("Input = %s \n",buf);	
	}

}

