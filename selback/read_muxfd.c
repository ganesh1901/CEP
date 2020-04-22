

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
	int fd1;
	int fd2;
	char buf[256];
	fd_set rfds;
        struct timeval tv;
        int retval;



	fd1 = open("fifo1",O_RDWR);
	fd2 = open("fifo2",O_RDWR);

	assert(fd1 > 0);
	assert(fd2 > 0);

	FD_ZERO(&rfds);
        FD_SET(fd1, &rfds);
        FD_SET(fd2, &rfds);

	/* Wait up to 100 seconds. */
        tv.tv_sec = 100;
        tv.tv_usec = 0;

        	
	z = select(2,&rfds,NULL,NULL,&tv);
        if (z <0 ){
                perror("select ");
                exit(1);
        }


	// Is FD1 Ready with Data
        if( FD_ISSET(fd1,&rfds)){
                z = read(fd1,buf,sizeof(buf));
                printf("Data1 = %s\n",buf);
        }

	// Is FD2 Ready With Data

        if( FD_ISSET(fd2,&rfds)){
                z = read(fd2,buf,sizeof(buf));
                printf("Data2 = %s\n",buf);
        } 


	return(0);	


}

