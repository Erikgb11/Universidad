#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(int argc,char** argv) {
	int x=0,y=1,z=1;
	printf("\t");
	while(" "){
		z=x+y;
		x=y;
		y=z;
		printf("\t%i",z);
	}
	return 0 ;
}
