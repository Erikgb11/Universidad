#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
int gcd(int u, int v){
	int a;
	while(v!=0){
		a=v;
		v=u%v;
		u=a;
	}
	return u;
}
void zn(int n){
	int z[n];
	for(int i=0;i<n;i++){
		if(gcd(n,i+1)==1){
			z[i]=i+1;
			printf("%d ",z[i]);
		}
	}
}

int xgcd(int a, int n){
	int u=a,v=n,q,r,x;
	int x1=1,x2=0;
	while(u!=1){
		q=v/u;
		r=v-(q*u);
		x=x2-(q*x1);
		v=u;
		u=r;
		x2=x1;
		x1=x;
	}
	if(x1<0)
		return n+x1%n;
	else
		return x1%n;	
}
void ac(int n){
    int a, b;
    srand(time(NULL));
    do{
        a= rand() % n;
    }while(gcd(a,n)!=1);
    do{
        b= rand() % n;
    }while(b<1);
    
    printf("K=(%d,%d)\n", a, b);
	printf("El inverso multiplicativo es: ");
    printf("%d^-1 mod %d = %d\n", a, n, xgcd(a,n));
    printf("Por lo tanto el GCD es: ");
    printf("gcd(%d,%d) = %d\n",a ,n ,gcd(a,n));
    
}
int main(){
	int a,n,mcd;
	printf("Ingrese el valor de a: \n");
	scanf("%d", &a);
	printf("Ingrese el valor de n: \n");
	scanf("%d", &n);
	if(n<=0&&a>=n){
		printf("recuerda que n>0 y a<n\n");
		return 0;
	}
	mcd=gcd(a,n);
	if(mcd!= 1){
		printf("recuerda que los numeros tienen que ser coprimos, intente de nuevo...\n");
		return 0;
	}
	else{
		printf("Por lo tanto el GCD es: ");
		printf("gcd(%d,%d)=%d\n", a,n,mcd);
	}	
	printf("El inverso multiplicativo es: ");
	printf("%d^-1 mod %d = %d\n", a, n, xgcd(a,n));

	printf("El conjunto de Z%d* es: ",n);
	zn(n);
	printf("\n");
	
	printf("\n Se creara una key con affine cipher\n");
	ac(n);
	return 0;
}
