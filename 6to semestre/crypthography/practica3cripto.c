//elaborado por Gonzalez Bocio Erik Alexander

#include <stdio.h>
#include <stdlib.h>
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
void binary(unsigned n,int t)
{
    unsigned i;
    for (i = 1 <<t-1; i > 0; i /= 2)//Se hace la impresión de t-1 cantidad de bits
        if(n & i){//Si se cumple el if
            printf("1");//Imprime 1
        }
        else//Si no
            printf("0"); //1
}
unsigned p10(unsigned n1,unsigned n2){//La segunda función que es para hacer la permutación de 10, llama dos unsigned 
//un unsigned guarda lo de la permutacion (n1) y el otro es el que tiene la cadena original (n2)
	BIT_WRITE(n1,9,BIT_GET(n2,7));//BIT_WRITE() cambia n1, en la posicion 9 pone lo que devuelve BIT_GET()
	//Por su parte BIT_GET() llama el valor 7 de n2, todo esto llendo de derecha a izquierda en los bits 
    BIT_WRITE(n1,8,BIT_GET(n2,5));
    BIT_WRITE(n1,7,BIT_GET(n2,8));
    BIT_WRITE(n1,6,BIT_GET(n2,3));
    BIT_WRITE(n1,5,BIT_GET(n2,6));
    BIT_WRITE(n1,4,BIT_GET(n2,0));
    BIT_WRITE(n1,3,BIT_GET(n2,9));
    BIT_WRITE(n1,2,BIT_GET(n2,1));
    BIT_WRITE(n1,1,BIT_GET(n2,2));
    BIT_WRITE(n1,0,BIT_GET(n2,4));
	return n1;//retorna n1
}
unsigned p8(unsigned n1,unsigned n2){//La segunda que es para permutar 8 bits
	BIT_WRITE(n1,7,BIT_GET(n2,4));//Hace lo mismo que en p10() solo que aqui es con 8 valores y la permutacion cambia
    BIT_WRITE(n1,6,BIT_GET(n2,7));
    BIT_WRITE(n1,5,BIT_GET(n2,3));
    BIT_WRITE(n1,4,BIT_GET(n2,6));
    BIT_WRITE(n1,3,BIT_GET(n2,2));
    BIT_WRITE(n1,2,BIT_GET(n2,5));
    BIT_WRITE(n1,1,BIT_GET(n2,0));
    BIT_WRITE(n1,0,BIT_GET(n2,1));
    return n1;//returna n1
}
unsigned corriz1(unsigned n1,unsigned n2){//La tercera función que es para hacer un corrimiento a la izq de 1, llama dos unsigned uno guarda el otro es el original
	for(int i=0;i<5;i++){//hace un for de 5
		if(i==0){//si i es igual a 0
			BIT_WRITE(n1,i,BIT_GET(n2,4));//la posicion i que es 0 se le da el valor 4
		}else{
			BIT_WRITE(n1,i,BIT_GET(n2,i-1));//de otro modo se le da el valor i-1, esto despues de un analisis que se llevo a cabo
		}
	}
	return n1;//returna n1
}
unsigned div5i(unsigned n1,unsigned n2){//despues tenemos el que parte la cadena de 10 bits y regresa la parte izquierda
	BIT_WRITE(n1,4,BIT_GET(n2,9));//hacemos uso de los método BIT_WRITE y BIT_GET en esta se les da los valores a la nueva variable de 0 a 4 con los valores de 5 a 9 del valor de 10 bits
    BIT_WRITE(n1,3,BIT_GET(n2,8));
    BIT_WRITE(n1,2,BIT_GET(n2,7));
    BIT_WRITE(n1,1,BIT_GET(n2,6));
    BIT_WRITE(n1,0,BIT_GET(n2,5));
	return n1;//returna n1
}
unsigned div5d(unsigned n1,unsigned n2){ //esta regresa la parte derecha de la division de 10 bits
	BIT_WRITE(n1,4,BIT_GET(n2,4));//aqui en la nueva variable se dan los valores de 0 a 4
    BIT_WRITE(n1,3,BIT_GET(n2,3));
    BIT_WRITE(n1,2,BIT_GET(n2,2));
    BIT_WRITE(n1,1,BIT_GET(n2,1));
    BIT_WRITE(n1,0,BIT_GET(n2,0));
	
	return n1;//returna n1
}
unsigned junt10(unsigned n1,unsigned n2,unsigned n3){//en esta juntamos dos cadenas de 5 en una de 10
	for(int i=10;i>=0;i--){//un for inverso
    	if(i>4){//cuando es menor a 4
    		BIT_WRITE(n1,i,BIT_GET(n2,i-5));//se le asigna el valor i-5 de la cadena derecha
		}else if(i<=5){//de lo contrario
			BIT_WRITE(n1,i,BIT_GET(n3,i));//se asigna el valor de i de la cadena izquierda
		}
	}
	return n1;//returna n1
}
unsigned div4i(unsigned n1,unsigned n2){//tambien esta la que divide 8 bits y esta es la que regresa la izquierda
	BIT_WRITE(n1,3,BIT_GET(n2,7));//se dan los valores de 4 a 7 a la variable
    BIT_WRITE(n1,2,BIT_GET(n2,6));
    BIT_WRITE(n1,1,BIT_GET(n2,5));
    BIT_WRITE(n1,0,BIT_GET(n2,4));
	return n1;//returna n1
}
unsigned div4d(unsigned n1,unsigned n2){//esta regresa la parte derecha
	BIT_WRITE(n1,3,BIT_GET(n2,3));//se dan los valores de 0 a 3 a la nueva variable
    BIT_WRITE(n1,2,BIT_GET(n2,2));
    BIT_WRITE(n1,1,BIT_GET(n2,1));
    BIT_WRITE(n1,0,BIT_GET(n2,0));
	return n1;//returna n1
}
unsigned corriz2(unsigned n1,unsigned n2){//se hace el corrimiento izquierdo esta vez de 2 posiciones
	for(int i=0;i<5;i++){//en un for de 0 a 4
		if(i>2){//si i es mayor a 2
			BIT_WRITE(n1,i,BIT_GET(n2,i-3));//se dan los valores de la posicion i-3 de n2
		}else{//si no
			BIT_WRITE(n1,i,BIT_GET(n2,i+2));//se dan los de i+2, esto despues de un analisis 
		}
	}
	return n1;//returna n1

}
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
void keys(long int cadena){//tenemos la función que hace todo aqui se ingresa un long int
	unsigned n1=0,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0,n8=0,n9=0,n10=0,n11=0;
	n1=binario(cadena);//se llama a la funcion binario para pasar el long int a unsigned
	printf("La key es:");
	binary(n1,10); //se imprime la key
    printf(" : %d\n", n1);//primer k
    printf("La key en hexadecimal es: %X\n",n1);//se imprime en hexadecimal con el formato %X
    SWAP1(n1,n2);//se pasa el valor de n1 a n2 y viceversa
    n1=p10(n1,n2);//se hace la permutacion de 10 bits
    binary(n1,10); 
    printf(" : %d\n", n1);
    n3=div5i(n3,n1);//se hace la division de la cadena permutada, aqui regresa la parte izquierda
    binary(n3,5);
    printf(" : %d\n", n3);
    n4=div5d(n4,n1);//aqui la parte derecha
    binary(n4,5); 
    printf(" : %d\n", n4);
	SWAP1(n4,n5);//se hace otro intercambio
	n4=corriz1(n4,n5);//se hace el corrimiento a la izquierda del valor derecho
	binary(n4,5); 
    printf(" : %d\n", n4);
    SWAP1(n3,n6);//otro intercambio
    n3=corriz1(n3,n6);//se hace el corrimiento del valor izquierdo
	binary(n3,5); 
    printf(" : %d\n", n3);
	n1=junt10(n1,n3,n4);
	binary(n1,10); 
    printf(" : %d\n", n1);
    n7=p8(n7,n1);//se hace la permutacion de 8 bits
    printf("La clave k1 es:");
    binary(n7,8); //k1
    printf(" : %d\n", n7);//se imprime k1 
    printf("La subclave k1 en hexadecimal es: %X\n",n7);//se imprime k1 en hexadecimal
    n8=div4i(n8,n7);//se hace la division izquierda
    binary(n8,5);
    printf(" : %d\n", n8);
    n9=div4d(n9,n7);//la division derecha
    binary(n9,5); 
    printf(" : %d\n", n9);
	n8=corriz2(n8,n6);//el corrimiento izq de dos posiciones del izquierdo
	binary(n8,5);
    printf(" : %d\n", n8);
	n9=corriz2(n9,n5);//el corrimiento de dos posiciones del derecho
	binary(n9,5);
    printf(" : %d\n", n9);
	n10=junt10(n10,n8,n9);//se juntan las dos partes
	binary(n10,10);
    printf(" : %d\n", n10);
    n11=p8(n11,n10);//se permuta en 8 
    printf("La clave k2 es:");//se imprime la segunda clave
    binary(n11,8); 
    printf(" : %d\n", n11);
    printf("La subclave k2 en hexadecimal es: %X\n",n11);//lo hacemos de nuevo en hexadecimal
}
int main(int argc, char *argv[]) {	//en la función main
	long int cadena; 
	printf("Ingrese el valor de la cadena\n");//pedimos la cadena a trabajar
	scanf("%ld",&cadena);
	printf("La cadena 1 es: %ld\n",cadena);
    keys(cadena);//y la pasamos por keys()
    return 0;//acaba el programa
}
