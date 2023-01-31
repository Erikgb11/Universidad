#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


int main(){
  ifstream arch("banner.txt", ifstream::in);
  int lin=0;
 
  while(arch.good()) if(arch.get()=='\n') lin++;
  cout <<"filas " <<lin ;

    ifstream archivo_entrada; 
    string linea;
arch.close (); //cerramos el arch
    archivo_entrada.open("banner.txt");    
    getline(archivo_entrada, linea);
    cout<< "\n";
   int col=linea.size();  // determinamos el tamaño de la lina del txt
     std::cout << "columnas  " <<  col ; //determinamos el tamaño por linea a la derecha 
     	 cout<< "\n";
int total = col *lin; // determinamos el total de los caracteres en el archivo
//Almacenamos los datos en la matriz principal

char letra; 
	char Principal [lin] [col];		//delimitamos la matriz total de todos los caracteres 
ifstream archivo ("banner.txt");
 if (archivo == NULL ){
 	cout<< "no se puede abrir el archivo";
 	}else{
		char letra; 
		for (int x=0 ; x<lin ; x++){ //recorremos filas
			for (int y=0 ; y<col ; y++){//recorremos columnas 
				archivo>>letra;
				Principal[x][y] =letra ;  //almacenamos todos los puntos en la matriz Principal 
			}
		}
		for (int x=0 ; x<lin ; x++){//recorremos filas
			for (int y=0 ; y<col ; y++){//recorremos columnas 
				cout <<Principal[x][y];;
			}
	 	cout<< "\n";	
		}
	//dividimos en 4 matrices secundarios para que sea mas rapido el proceso de imprecion
	}
}

