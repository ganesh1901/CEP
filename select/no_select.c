       
// The code is intentional and for the use of V&V CEP Demo purpose only.
// Do not try use the code as it is 
// Author V&V Team   DCCT/DRDL.


       #include <stdio.h>
       #include <stdlib.h>
       #include <sys/time.h>
       #include <sys/types.h>
       #include <unistd.h>
       #include <termios.h>
       #include <unistd.h>
       #include <sys/ioctl.h>

	#define NB_ENABLE 1  
	#define NB_DISABLE 0 
	



int kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}	

		
	
void nonblock(int state)
{
    struct termios ttystate;
 
    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);
 
    if (state==NB_ENABLE)
    {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else if (state==NB_DISABLE)
    {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
 
}	
	


       int
       main(void)
       {
           int nbytes=0;
	   int fd;
	   char buffer[80];
           char c;	
	   int i = 0;


           // Watch on stdin (fd 0) to see when it has input Entered thru Keypad i.e input device 


    while(!kbhit()) {

   }


              


    fgets(buffer,sizeof(buffer),stdin);
    printf("Data Read = %s \n",buffer);
 
    nonblock(NB_DISABLE);
    return (0);
}


