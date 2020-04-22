

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
	
        int retval;
	int z;
	int fd1;
	int fd2;
	int nfds;
	char buf[256];
	fd_set rxset;
        struct timeval tv;
	FILE *fp1,*fp2;



/*	if(!(fp1 = popen("ls -ltr","r"))) {
		perror("Unable to open PIPE1 \n");
		exit(-1);	
	}

	if(!(fp2 = popen("df -h","r"))) {
		perror("Unable to open PIPE2 \n");
		exit(-1);	
	} 

	fd1 = fileno(fp1);
	fd2 = fileno(fp2);  */

	

        fd1 = open("fifo1",O_RDWR);
        fd2 = open("fifo2",O_RDWR);




	assert(fd1 > 0);
        assert(fd2 > 0);



		FD_ZERO(&rxset);
        	FD_SET(fd1, &rxset);
	        FD_SET(fd2, &rxset);

		nfds = (fd1 > fd2 ? fd1 : fd2 ) + 1;

		printf("NFDS = %d \n",nfds);

		/* Wait up to 100 seconds. */
	        tv.tv_sec = 100;
        	tv.tv_usec = 0;

		

		retval = select(nfds,&rxset,NULL,NULL,&tv);

		if( retval == -1) {
			printf("Select Failed ...! \n");
			exit(1);
		}

		if( retval == 0) {
			printf("No Data Timed Out \n");
			exit(-1);
		}
		if(FD_ISSET(fd1,&rxset)) {
			printf("Data Ready On FD1 \n");
			z = read(fd1,buf,sizeof(buf));
			printf("Data2 = %s \n",buf);
			close(fd1);
			fd1=-1;
		}	

		if(FD_ISSET(fd2,&rxset)) {
			printf("Data Ready On FD2 \n");
			z = read(fd2,buf,sizeof(buf));
			printf("Data2 = %s \n",buf);
			close(fd2);
			fd2 = -1;
		}	


	return(0);	


}

