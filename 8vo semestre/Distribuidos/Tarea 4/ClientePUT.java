import java.io.*;
import java.net.*;
import javax.net.ssl.*;

public class ClientePUT{
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
        
        // Verificar si el archivo existe y puede ser leído
        File file = new File(fileName);
        if (!file.exists() || !file.canRead()) {
            System.err.println("No se puede leer el archivo: " + fileName);
            System.exit(1);
        }
        // Crear un socket seguro
        SSLSocketFactory sslsocketfactory = (SSLSocketFactory) SSLSocketFactory.getDefault();
        SSLSocket sslsocket = (SSLSocket) sslsocketfactory.createSocket(host, port);

        // Enviar una petición PUT con el nombre del archivo y la longitud
        OutputStream out = sslsocket.getOutputStream();
        String request = "PUT " + fileName + " " + file.length() + "\r\n";
        out.write(request.getBytes());
        out.flush();

        // Enviar el contenido del archivo
        FileInputStream fileInputStream = new FileInputStream(file);
        byte[] buffer = new byte[1024];
        int bytesRead;
        while ((bytesRead = fileInputStream.read(buffer)) != -1) {
            out.write(buffer, 0, bytesRead);
        }
        fileInputStream.close();
        out.flush();

        // Leer la respuesta del servidor
        BufferedReader in = new BufferedReader(new InputStreamReader(sslsocket.getInputStream()));
        String response = in.readLine();
        if (response.equals("OK")) {
            System.out.println("El archivo fue recibido por el servidor con éxito.");
        } else {
            System.err.println("El servidor no pudo escribir el archivo en el disco local.");
        }

        // Cerrar el socket
        sslsocket.close();
    }
}
