import java.io.*;
import java.net.*;

public class servidorB{
    static class Worker extends Thread {
        Socket conexion;
        Worker(Socket conexion) {
            this.conexion = conexion;
        }
        public void run() {
            try{
                DataInputStream entrada = new DataInputStream(conexion.getInputStream());
                DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
                long numero=entrada.readLong();
                String divide = null;
                long dividos = numero / 2;
                long numeroInicial = 2;
                long numeroFinal = 0;
                int puerto = 55556;
                Socket conexion = null;
                int primo = 0;
                System.out.println("El numero a trabajar es: "+numero);
                for (int i = 0; i < 3; i++) {
                    try {
                        conexion = new Socket("Localhost", puerto);
                        puerto++;
                        DataOutputStream salidaSocket = new DataOutputStream(conexion.getOutputStream());
                        DataInputStream entradaSocket = new DataInputStream(conexion.getInputStream());
                        if (i != 0) {
                            numeroInicial = numeroFinal + 1;
                        }
                        numeroFinal = (dividos / 3) * (i + 1);
                        salidaSocket.writeLong(numero);
                        salidaSocket.writeLong(numeroInicial);
                        salidaSocket.writeLong(numeroFinal);
                        divide=entradaSocket.readUTF();
                        System.out.println("El Intervalo " + (i + 1) + " va de " + numeroInicial + " al " + numeroFinal + " y " + divide );
                        if (divide.equals("DIVIDE")) primo++;
                        salidaSocket.close();
                        entradaSocket.close();
                        conexion.close();
                    } catch (Exception e) {
                        Thread.sleep(200);
                        System.err.println(e.getMessage());
                    }
                } 
                System.out.println("Por lo que el numero: ");
                if(primo>0){
                    System.out.println("NO ES PRIMO");
                    salida.writeUTF("NO ES PRIMO");

                }else{
                    System.out.println("ES PRIMO");
                    salida.writeUTF("ES PRIMO");
                }
            }catch (Exception e) {
                System.err.println(e.getMessage());
            }
        }
    }
    public static void main(String[] args) throws Exception {
        ServerSocket servidor = new ServerSocket(55555);
        for (; ; ) {
            Socket conexion = servidor.accept();
            new Worker(conexion).start();
        }
    }
}
    
