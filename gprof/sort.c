

// The following Code is a demonstration purpose of Priority Inversion During V&V CEP 9/07/12
// // Most of the code is written intentional to only demonstrate the purpose , don't try to use as it is
// // Author V&V Team
//

#include <stdio.h>

#define MAX_ELEMENTS 10000


//insertion sort
void testUnit(int list[], int Size) {

	int i,j,temp;
	
	for(i=1;i<=Size-1;i++) {
		temp = list[i];
		for(j = i -1; j >=0 && (list[j] > temp); j--) {
			list[j+1] = list[j];
		}
		list[j+1] = temp;
	}


} 

void init_list(int list[], int Size) {
	int i;
	for(i=0;i<Size;i++) {
		list[i] = Size - i;
	}

}

int main() {

	int list[MAX_ELEMENTS]; 
	int i;
	
	init_list(list,MAX_ELEMENTS);

//	for(i=0;i<MAX_ELEMENTS;i++) 
//		printf("%d \n",list[i]);

	testUnit(list,MAX_ELEMENTS);	

//	for(i=0;i<MAX_ELEMENTS;i++) 
//		printf("%d \n",list[i]);
	return(0);
}
