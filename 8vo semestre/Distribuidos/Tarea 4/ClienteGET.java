import java.io.*;
import java.net.*;
import javax.net.ssl.*;

public class ClienteGET{
    public static void main(String[] args) throws Exception {
        if (args.length != 3) {
            System.err.println("Uso: java Cliente <ip del servidor> <puerto> <nombre del archivo>");
            System.exit(1);
        }

        String host = args[0];
        int port = Integer.parseInt(args[1]);
        String fileName = args[2];

        System.setProperty("javax.net.ssl.trustStore","keystore_cliente.jks");
        System.setProperty("javax.net.ssl.trustStorePassword","1234567");

        // Crear un socket seguro
        SSLSocketFactory sslsocketfactory = (SSLSocketFactory) SSLSocketFactory.getDefault();
        SSLSocket sslsocket = (SSLSocket) sslsocketfactory.createSocket(host, port);

        // Enviar una petición GET con el nombre del archivo
        OutputStream out = sslsocket.getOutputStream();
        PrintWriter ouut = new PrintWriter( out, true);
        //String request = "GET " + fileName + "\r\n";
        String peticion = "GET";
        String fileN= fileName;
        ouut.println(peticion);
        out.flush();
        ouut.println(fileN);
        out.flush();

        // Leer la respuesta del servidor
        BufferedReader in = new BufferedReader(new InputStreamReader(sslsocket.getInputStream()));
        String response = in.readLine();
        if (!response.equals("OK")) {
            System.err.println("El servidor no pudo encontrar el archivo solicitado.");
            System.exit(1);
        }

        // Leer la longitud del archivo
        long fileLength = Long.parseLong(in.readLine());

        // Recibir el contenido del archivo y escribirlo en el disco local
        FileOutputStream fileOutputStream = new FileOutputStream(new File(fileName));
        byte[] buffer = new byte[1024];
        int bytesRead;
        long totalBytesRead = 0;
        while (totalBytesRead < fileLength && (bytesRead = sslsocket.getInputStream().read(buffer)) != -1) {
            fileOutputStream.write(buffer, 0, bytesRead);
            totalBytesRead += bytesRead;
        }
        fileOutputStream.close();

        // Verificar que se recibió todo el archivo
        if (totalBytesRead != fileLength) {
            System.err.println("El archivo se recibió de forma incompleta.");
            System.exit(1);
        }

        // Cerrar el socket
        sslsocket.close();

        // Indicar que el archivo se recibió con éxito
        System.out.println("El archivo se recibió con éxito.");
    }
}
