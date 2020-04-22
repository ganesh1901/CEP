#include <stdio.h>

struct bitfield {

  int b:1;

}bit;



int main() {

	bit.b = 1;
	printf("Bit = %d \n",bit.b);
	bit.b++;
	printf("Bit = %d \n",bit.b);

}
