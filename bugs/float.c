#include <stdio.h>

float compute () {
	int k=-1;
//	return(4.x.0);
	return(sqrt(k));
}

int main() {

	float f;
	float x=0.0;

	printf("F = %f \n",f);

	f=compute();

	printf("F == %f \n",f);

	if(f != f) {
		printf("Not Equal != \n");
	} else {
		printf("Alternate flow of f != f \n");
	}

	if(f == f) {
		printf("They are Eqaul f == f \n");
	} else {
		printf("Alternate Flow of f == f \n");
	}

	if(f == x) {
		printf("Equal to x  f == x \n");
	} else {
		printf("Alternate Flow of f == x \n");
	}


	if(f > x) {
		printf("Not Greater Than x \n");
	} else {
		printf("Alternate FLow of f > x \n");
	}
	
	if(f < x) {
		printf("Less than x \n");		
	} else {

		printf("Alternate Flow of f < x \n");
	} 



	

		

}
