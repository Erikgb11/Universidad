
import java.io.IOException;
import java.security.SecureRandom;
import java.util.Base64;
import java.util.Scanner;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author escom
 * Developed by Gonzalez Bocio Erik Alexander
 * 05/03/22
 */
public class terfun {
    public static String base64(byte[] key) {//Función base64, pasa de bytes a base 64
        String b64;
        Base64.Encoder encoder = Base64.getEncoder(); //Se hace el método para pasar a base64
        b64 = encoder.encodeToString(key);//Se aplica el método al array de bytes que entra, pasandolo a un string
        return b64; //Retorna el string
    }
    public static byte[] elbyte(String b64) {//Función elbyte() que pasa de base64 a bytes
        byte[] elbyt = Base64.getDecoder().decode(b64);//Se pasa el string base64 a bytes
        return elbyt;//retorna el array
    }
    public static String bin(int length) {//Función bin() que genera el array de bytes aleatorios
        SecureRandom rand = new SecureRandom(); //Se usa Securerandom para generar los numeros aleatorios
        byte [] k = new byte[length];
        rand.nextBytes(k);//Se generan bytes aleatorios y se guardan en el array 
        String b64=base64(k);//Se pasa de bytes a base64
        return b64;//Se retorna el array
    }
    public static String encipher(String plaintext) {// Función que hace el cifrado
        int length = plaintext.length();
        byte[] encip = new byte[length];
        byte[] pt = plaintext.getBytes();//se pasa el plaintext a bytes
        String b64=bin(length);//se crean los bytes aleatorios
        byte[] k = new byte[length];
        k= elbyte(b64);//se hace la key pasandola a base 64
        for(int i = 0; i<length ; i++){ 
            encip[i] = (byte) (k[i] ^ pt[i]); //se hace el xor
        }
        String cifradin=base64(encip);//se pasa el mensaje cifrado a base64
        /*System.out.println("El valor del xor es: "+encip;)*/
        System.out.println("Su texto cifrado es : "+cifradin);
        System.out.println("Y su llave: "+b64);
      return cifradin;//se imprimen el texto cifrado, la key y se retorna la primera
    }
    
    public static String descipher(String c,String k) {//Función que hace el descifrado
        byte[] text=elbyte(c);//se pasa el texto a bytes
        byte[] key=elbyte(k);//Se pasa la key a bytes
        int length = text.length;
        byte[] desci=new byte[length];
        for(int i = 0; i<length; i++){
            desci[i] = (byte) (text[i] ^ key[i]); //se hace el xor de el texto cifrado y la key
        }
        String plaintext = new String(desci);//Se convierte el texto a String
        System.out.println("El texto descifrado es : "+plaintext);
        return plaintext;//Se imprime el plaintext y se retorna
    }
    
    public static void main(String args[]) throws IOException{//Main principal
        Scanner entrada = new Scanner(System.in);//Scanner
        Scanner entrada2 = new Scanner(System.in);//Scanner
        int choose;
        String plaintext,c;
        System.out.println("Developed by Gonzalez Bocio Erik");
        System.out.println("Stream Ciphers");
        System.out.println("Programa para cifrar y descifrar texto simulando one-time pad");
        do{
            System.out.println("Selecciona la opción deseada");//Se hace el menú para ver que elegir 
            System.out.println("1. Cifrar");
            System.out.println("2. Descifrar");
            System.out.println("3. Salir");
            choose = entrada.nextInt();
            String key,i;
            switch(choose){
                case 1://Si se elige 1 se cifra
                    System.out.println("Hola, ingresa por favor el plaintext");
                    plaintext= entrada2.nextLine();//Se pide el texti y se ingresa
                    c= encipher(plaintext); //Se hace uso de la funcion para descifrar
                    System.out.println("Quieres intentar descifrar tu mensaje cifrado?[si/no]");
                    i = entrada2.nextLine();//Pregunta si quieres descifrar
                    if(i.equals("si")||i.equals("Si")||i.equals("SI")||i.equals("sI")){//Si dice que si se hace el descifrado
                        System.out.println("Ingrese la key");
                        key = entrada2.nextLine();//Se pide la key
                        String d= descipher(c,key);//Se descifra con la función
                        System.out.println("Volviendo al menu...");
                        break;
                    }else if(i.equals("no")||i.equals("No")||i.equals("NO")||i.equals("nO")){//Si dice que no se regresa al menú
                        System.out.println("Volviendo al menu...");
                        break;
                    }else{//en otro caso se regresa al menu
                        System.out.println("Tomare eso como un no");
                        System.out.println("Volviendo al menu...");
                        break;
                    }
                case 2://Si se elige 2 se descifra
                    String cifrado;
                    System.out.println("Ingrese el texto cifrado");
                    cifrado = entrada2.nextLine();//Se pide el texto cifrado
                    System.out.println("Ingrese la key");
                    key = entrada2.nextLine();//Se pide la key
                    String d= descipher(cifrado,key);//Se descifra con la funcion de descifrado pasandole el cifrado y la key
                    break;
                case 3://Si se elige 3 se sale
                     System.exit(0);//Se sale
                default://Otra opcion se repite el menu
                    System.out.println("Lo siento esa opción no esta disponible,vuelva intentarlo");
                    break;
            }
            choose=0;//Se regresa el valor para elegir a '
        }while(choose==0);
        
    }

}
