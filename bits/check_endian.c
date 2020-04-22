#include <stdio.h>


int main() {

	unsigned short  k=0x0001;

	printf("size of int = %d long = %d bytes \n",sizeof(int),sizeof(long));

	if(*((char *)&k) & 0x0001 == 1) {
		printf("Little Endian \n");
	} else {
		printf("Big Endian \n");
	}
	return(0);
} 
