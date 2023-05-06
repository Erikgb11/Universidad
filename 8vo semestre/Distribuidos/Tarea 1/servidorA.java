import java.io.*;
import java.net.*;

public class servidorA{
    static Object obj = new Object();
    static int primo = 0;
    static class Worker extends Thread {
        Socket conexion;
        Worker(Socket conexion) {
            this.conexion = conexion;
        }
        public void run() {
            try {
                String divide = null;
                DataOutputStream salida = new DataOutputStream(conexion.getOutputStream());
                DataInputStream entrada = new DataInputStream(conexion.getInputStream());
                long numero = entrada.readLong();
                long numeroInicial = entrada.readLong();
                long numeroFinal = entrada.readLong();
                System.out.println("El intervalo entre "+numeroInicial+" y "+numeroFinal+" :");
                synchronized (obj) {
                    for (long i = numeroInicial; i <= numeroFinal; i++) {
                        if (numero % i == 0) {
                            primo++;
                            System.out.println("el numero: " + i);
                            divide = "DIVIDE";
                            salida.writeUTF(divide);
                            System.out.println("DIVIDE");
                            break;
                        }
                    }
                    if (primo == 0) {
                        System.out.println("NO DIVIDE");
                        divide = "NO DIVIDE";
                        salida.writeUTF(divide);
                    }
                }
                entrada.close();
                salida.close();
                conexion.close();
            } catch (Exception ex) {
                System.err.println(ex.getMessage());
            }
        }
    }
    public static void main(String[] args) throws Exception {
        int port = Integer.valueOf(args[0]);
        ServerSocket servidor = new ServerSocket(port);
        Socket conexion = servidor.accept();
        Worker w = new Worker(conexion);
        w.start();
        w.join();
    }
}