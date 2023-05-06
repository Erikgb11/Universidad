import java.io.*;
import java.net.*;

public class client {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("Localhost", 55555);
            System.out.println("Ingrese el numero por favor:");
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            DataInputStream entrada = new DataInputStream(socket.getInputStream());
            DataOutputStream out = new DataOutputStream(socket.getOutputStream());
            Long numero  = Long.parseLong(br.readLine());
            out.writeLong(numero);
            String prim=null;
            prim=entrada.readUTF();
            System.out.println("El numero "+numero+" "+ prim);
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
