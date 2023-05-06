import java.io.IOException;
import java.net.*;
import java.util.Scanner;

public class MulticastChat {
    
    static class Worker extends Thread {
        MulticastSocket socket;
        String username;
        
        public Worker(MulticastSocket socket, String username) {
            this.socket = socket;
            this.username = username;
        }
        
        @Override
        public void run() {
            byte[] buffer = new byte[256];
            while (true) {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                try {
                    socket.receive(packet);
                    String message = new String(packet.getData(), 0, packet.getLength(), "ISO-8859-1");
                    System.out.println(message);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        if (args.length < 1) {
            System.out.println("Usage: java MulticastChat <username>");
            return;
        }
        
        String username = args[0];
        MulticastSocket socket = new MulticastSocket(50000);
        InetAddress group = InetAddress.getByName("239.0.0.0");
        socket.joinGroup(group);
        
        Worker worker = new Worker(socket, username);
        worker.start();
        
        Scanner scanner = new Scanner(System.in);
        while (true) {
	    System.out.println("Escribe tu mensaje: ");
            String message = scanner.nextLine();
            message = message.trim().replaceAll("\\s+", " ");
            String formattedMessage = username + "--->" + message;
            byte[] data = formattedMessage.getBytes("ISO-8859-1");
            DatagramPacket packet = new DatagramPacket(data, data.length, group, 50000);
            socket.send(packet);
        }
    }
}
