#include <iostream>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int Division1(int n,int div,int res);
int Division2(int n,int div);
int Division3(int n,int div);
int Division1(int n,int div,int res){
	int q=0,c=0;
	c++;
	while(n>=div){
		c++;
		n=n-div;
		c+=2;
		q=q+1;
		c+=2;
	}
	c+=2;
	printf("El valor del contador es: %d\n",c);
	return q;
	
}
int Division2(int n,int div){
	int c=0;
	int dd=div;
	c++;
	int q=0;
	int r=n;
	while(dd<=n){
		c++;
		dd=2*dd;
		c+=2;
	}c++;
	while(dd>div){
		c++;
		dd=dd/2;
		c+=2;
		q=2*q;
		c+=2;
		if(dd<=r){
			c++;
			r=r-dd;
			c+=2;
			q=q+1;
			c+=2;			
		}c++;		
	}
	c+=2;
	printf("El valor del contador es: %d\n",c);
	return q;
}
int Division3(int n,int div){
	int c;
	if(div>n){
		c+=2;
		//printf("El valor del contador es: %d\n",c);
		return 0;
	}else{
		c+=3;
		printf("El valor del contador es: %d\n",c);
		return 1+Division3(n-div,div);
	}
}
int main(){
	int n,a,b,c,res=0,div=2;
	for(int n=0;n<=20;n++){
			printf("Con los valores de %d y %d, tenemos:\n",n,div);
			//a=Division1(n,div,res);
			//b=Division2(n,div);
			c=Division3(n,div);	
			//printf("El cociente es:%d\n",a);
			//printf("El cociente es:%d\n",b);
			printf("El cociente es:%d\n",c);	
	}
	
	
	
	
}
