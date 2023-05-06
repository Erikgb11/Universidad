import java.io.*;
import java.net.*;
import javax.net.ssl.*;

public class Servidor {
    public static void main(String[] args) throws Exception {
        System.setProperty("javax.net.ssl.keyStore","keystore_servidor.jks");
        System.setProperty("javax.net.ssl.keyStorePassword","1234567");
        // Configurar el socket seguro
        SSLServerSocketFactory sslserversocketfactory = (SSLServerSocketFactory) SSLServerSocketFactory.getDefault();
        SSLServerSocket sslserversocket = (SSLServerSocket) sslserversocketfactory.createServerSocket(50000);

        System.out.println("Servidor en línea y esperando conexiones...");

        while (true) {
            // Esperar a que un cliente se conecte
            SSLSocket sslsocket = (SSLSocket) sslserversocket.accept();
            System.out.println("Cliente conectado.");

            // Manejar la solicitud del cliente en un hilo separado
            Thread thread = new Thread(new ClientHandler(sslsocket));
            thread.start();
        }
    }
}

class ClientHandler implements Runnable {
    private SSLSocket sslsocket;

    public ClientHandler(SSLSocket sslsocket) {
        this.sslsocket = sslsocket;
    }

    public void run() {
        try {
            // Leer la petición del cliente
            BufferedReader in = new BufferedReader(new InputStreamReader(sslsocket.getInputStream()));
            String peticion = in.readLine();
            String fileName = in.readLine();
            //String[] requestParts = request.split(" ");

            // Manejar la petición GET
            if (peticion.equals("GET")) {
                // Leer el archivo del disco local
                FileInputStream fileInputStream = null;
                try {
                    fileInputStream = new FileInputStream(fileName);
                } catch (FileNotFoundException e) {
                    System.err.println("No se encontró el archivo " + fileName);
                    sendErrorResponse();
                    return;
                }

                // Enviar una respuesta OK con la longitud del archivo y el contenido del
                // archivo
                OutputStream out = sslsocket.getOutputStream();
                out.write("OK\r\n".getBytes());

                long fileLength = new File(fileName).length();
                out.write((fileLength + "\r\n").getBytes());

                byte[] buffer = new byte[1024];
                int bytesRead;
                while ((bytesRead = fileInputStream.read(buffer)) != -1) {
                    out.write(buffer, 0, bytesRead);
                }

                fileInputStream.close();
                out.flush();
                out.close();
            }

            // Manejar la petición PUT
            else if (peticion.equals("PUT")) {
                long fileLength = Long.parseLong(in.readLine());
                // Escribir el archivo en el disco local
                FileOutputStream fileOutputStream = null;
                try {
                    fileOutputStream = new FileOutputStream(fileName);
                } catch (FileNotFoundException e) {
                    System.err.println("No se pudo escribir el archivo " + fileName);
                    sendErrorResponse();
                    return;
                }

                byte[] buffer = new byte[1024];
                int bytesRead;
                long totalBytesRead = 0;
                while (totalBytesRead < fileLength && (bytesRead = sslsocket.getInputStream().read(buffer)) != -1) {
                    fileOutputStream.write(buffer, 0, bytesRead);
                    totalBytesRead += bytesRead;
                }

                fileOutputStream.close();

                // Enviar una respuesta OK si se pudo escribir el archivo en el disco local
                if (totalBytesRead == fileLength) {
                    OutputStream out = sslsocket.getOutputStream();
                    out.write("OK\r\n".getBytes());
                    out.flush();
                    out.close();
                } else {
                    System.err.println("No se pudo escribir el archivo " + fileName);
                    sendErrorResponse();
                }
            }

            // Manejar una petición desconocida
            else {
                System.err.println("Petición desconocida: " + peticion);
                sendErrorResponse();
            }

        } catch (IOException e) {
            System.err.println("Error al manejar la petición del cliente: " + e.getMessage());
        } finally {
            try {
                sslsocket.close();
            } catch (IOException e) {
                System.err.println("Error al cerrar la conexión con el cliente: " + e.getMessage());
            }
        }
    }

    private void sendErrorResponse() throws IOException {
        OutputStream out = sslsocket.getOutputStream();
        out.write("ERROR\r\n".getBytes());
        out.flush();
        out.close();
    }

}