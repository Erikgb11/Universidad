//elaborado por Gonzalez Bocio Erik Alexander
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef MAX
#define MAX 100
#endif
#define BIT(x)         (1<<(x))
#define BIT_GET(x,b)   ((x) & BIT(b))
#define BIT_SET(x,b)   ((x) |= BIT(b))
#define BIT_CLEAR(x,b) ((x) &= ~BIT(b))
#define BIT_TOGGLE(x,b)  ((x) ^= BIT(b))
#define BIT_WRITE(x,b,v) ((v)? BIT_SET(x,b) : BIT_CLEAR(x,b))
#define ES_PAR(x) (!BIT_GET(x,0))
#define SWAP1(x,y) (x = x ^ y ,  y = x ^ y ,  x = x ^ y )
#define SWAP2(x,y) (x^=y^=x^=y)
#define SWAP3(x,y) (x^=y^=x^=y^=x^=y^=x^=y^=x^=y)

//Estas definiciones son de métodos que se usan para poder trabajar con unsigned a nivel de bits
//Tenemos la primer función
unsigned binario(long int binario){//esta funcion pasa de un long int a un unsigned 
	int exp=0;
	unsigned decimal=0;
   	while((binario/10)!=0)///mientras el long int sea diferente de 0
   	{
           int digito = binario % 10;// digito=binario modulo 10
           decimal = decimal + digito * pow(2.0,exp);//decimal= decimal +digito+ exp al cuadrado
           exp++;//se incrementa exp
           binario=(binario/10);//se hace un llamado recursivo metiendole binario/10
   	}
   	decimal=decimal + binario * pow(2.0,exp);//decimal=decimal+binario+exp al cuadrado
	return decimal;//returna decimal
}

void binary(unsigned char n,int t)
{
    unsigned i;
    for (i = 1 <<t-1; i > 0; i /= 2)//Se hace la impresión de t-1 cantidad de bits
        if(n & i){//Si se cumple el if
            printf("1");//Imprime 1
        }
        else//Si no
            printf("0"); //1
}
void binrep(unsigned char n, int t){
	 unsigned i;
	 int conta=t-1;
	 int c=0;
    for (i = 1 <<t-1; i > 0; i /= 2)//Se hace la impresión de t-1 cantidad de bits
        if(n & i){//Si se cumple el if
        	if(c>0){
            	printf("+");//si c es mayor a 0 entonces agrega un +
			}
        	printf("x^%d",conta);//imprime x^n donde n es el valor de conta
        	conta--;//va restando el contador conta
        	c++;//va aunmentando el contador x
        }
        else//Si no
            conta--;//cuando es 0 va restando
}

int ultimouno(unsigned char a){
	unsigned i;
	int t=4;
	int c=3,c2=0;
    for (i = 1 <<t-1; i > 0; i /= 2){//Se hace la impresión de t-1 cantidad de bits
        if(a & i){//Si se cumple el if
        	c=c-c2;//se le resta a c c2
			return c;//y se retorna
        }else{//de otro modo
        	c2++;//se aumenta el contador
		}
	}
	return c;	//se retorna el c
}
unsigned char corrimiento(unsigned char b){
	unsigned char a=b;	
	for(int i=0;i<4;i++){//hace un for de 4
		if(i==0){//si i es igual a 0
			BIT_WRITE(b,i,BIT_GET(a,3));//la posicion i que es 0 se le da el 3er valor
		}else{
			BIT_WRITE(b,i,BIT_GET(a,i-1));//de otro modo se le da el valor i-1, esto despues de un analisis que se llevo a cabo
		}
	}
	return b;//returna n1
}
unsigned char corrimiento2(unsigned char b){
	unsigned char a=b;	
	for(int i=0;i<4;i++){//hace un for de 4
		if(i==0){//si i es igual a 0
			BIT_WRITE(b,i,0);//la posicion i que es 0 se le da el valor 0
		}else{
			BIT_WRITE(b,i,BIT_GET(a,i-1));//de otro modo se le da el valor i-1, esto despues de un analisis que se llevo a cabo
		}
	}
	return b;//returna n1	
}
int numerosuno(unsigned char a){
	int conta=0;
	for(int i=0;i<4;i++){//se hace un for hasta 4
		if(BIT_GET(a,i)!=0){//se obtiene el valor i de a y si es diferente de 0
			conta++;//aumenta el contador
		}
	}
	return conta;//y lo retorna
}
void posiunos(unsigned char a,int *unos){
	int conta=0;
	for(int i=0;i<4;i++){//se hace un for hasta 4
		if(BIT_GET(a,i)!=0){//se obtiene el valor i de a y si es diferente de 0
			unos[conta]=i;//se agrega el valor de i a un array para guardar la posicion
			conta++;//se aumenta el contador
		}
	}
	return;
}
unsigned char modu(unsigned char a, unsigned char b){
	int z=ultimouno(a);//se obtiene la posicion del ultimo uno en a
	unsigned char modu=3;//el valor del residuo 
	unsigned char resultados[z];
	resultados[0]=b;//se da el valor de b a la primera posicion del array de los resultados
	for(int i=1;i<=z;i++){//un if hasta z, o la ultima posicion del 1 en a
		if(BIT_GET(b,3)==0){//si el valor del primer bit es 0
			b=corrimiento(b);//hace un corrimiento a la izquierda 
		}else if(BIT_GET(b,3)!=0){//si es diferente
			b=corrimiento2(b);//se hace un corrimiento con corrimiento 2
			b=b^modu;//hace un xor con el residuo
		}
		resultados[i]=b;//se agregan los valores de b un array
	}
	int lenght=numerosuno(a);//se saca el valor de los numeros 1 en a
	int unos[lenght];//se hace un array con esa longitud
	posiunos(a,unos);//y se guardan las posiciones de dichos 1's
	unsigned char resultado=resultados[unos[0]];
	for(int i=1;i<lenght;i++){
		resultado=resultado^resultados[unos[i]];//luego se sacan las posiciones y se hacen los xor dependiendo de las posiciones
	}
	return resultado;//se retorna el resultado
}

int arch(){
	FILE *fp = fopen("tablamult.txt", "w");//se guarda en el archivos tablamult.txt
	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}
	char linea[80];//se declara linea con la que trabajaremos
	char poli[20]="";
	unsigned char matriz[16][16];//se hace una matriz donde se guardan los resultados
	unsigned char num[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//un array con numeros de 0 al 15
	for(int i=1;i<16;i++){
		for(int j=1;j<16;j++){//dos for anidados donde se haran las multplicaciones con modu() y se guardaran en una matriz
			matriz[i][j]=modu(num[i],num[j]);
		}
		printf("\n");
	}
	sprintf(linea, "Tabla de multiplicar GF(2^4)\n");
	fputs(linea, fp);
	for (int i = 1; i < 16; i++) {
		linea[0] = '\0';
		for (int j = 1; j < 16; j++) {
			char buffer[10];
			sprintf(buffer, "%d    ", matriz[i][j]);//se guardan en buffer los valores de la matriz
			strcat(linea, buffer);//y se concatenan con linea
		}
		int len = strlen(linea);//se saca el tamaño de dicha linea
		linea[len - 1] = '\n';
		fputs(linea, fp);//y se guardan
	}
	fclose(fp);//se cierra el archivo.
}

int main(){
	int n, opcion;
	long int cadena;
    do
    {
        printf( "\n1. Representación polinomial de una cadena binaria.", 163 );//se preguntan los casos
        printf( "\n2. Calcular a(x)*b(x) mod (x^4+x+1) ", 163 );
        printf( "\n3. Tabla de multiplicación para GF(2^4).", 163 );
        printf( "\n4. Salir." );
        printf( "\n\nIntroduzca opci%cn (1-4): ", 162 );
        scanf( "%d", &opcion );
        switch ( opcion )
        {
            case 1: //caso 1
            		printf("\n");
					printf("Ingrese el valor de la cadena\n");//pedimos la cadena a trabajar
					scanf("%ld",&cadena);
					unsigned char c;
					c=binario(cadena);//se convierte a unsigned char
					binrep(c,4);//se hace la representacion con binrep()
					printf("\n");
                    break;//acaba
        	case 2: unsigned char res;
            		printf("\n");
					printf("Ingrese el valor de la cadena a\n");//pedimos la cadena a trabajar
					scanf("%ld",&cadena);
					unsigned char a;
					a=binario(cadena);//se converite a unsigned
					printf("Ingrese el valor de la cadena b\n");//pedimos la cadena a trabajar
					scanf("%ld",&cadena);
					unsigned char b;
					b=binario(cadena);//se converite a unsigned
					res=modu(a,b);//se hace la multiplicacion con modu()
					binary(res,4);//se imprime con binary()
					printf("\n");
                    break;//se acaba
        	case 3: 	arch();//se hace lo de guardar la tabla en un archivo con arch()
        				break;//se acaba
         }
    } while ( opcion != 4 );
    return 0;
	
}
