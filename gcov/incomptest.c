

// The following Code is a demonstration purpose of Priority Inversion During V&V CEP 9/07/12
// // Most of the code is written intentional to only demonstrate the purpose , don't try to use as it is
// // Author V&V Team
//

#include <stdio.h>

int testUnit(int a,int b) {



	if( a == 1 )  {
		printf(" a = 1 \n");
	} else  {
		printf(" a != 1 \n");
	}

	if( b == 1 )  {
		printf(" b = 1 \n");
	} else  {
		printf(" b != 1 \n");
	}

	return(0);
} 

int main() {

	testUnit(1,2);
}
