import java.util.*;
import java.net.*;
import java.io.*;

public class MultiplicacionMatrices {
    static int N = 3000;
    static int PUERTO_SERVIDOR_1 = 60001;
    static int PUERTO_SERVIDOR_2 = 60002;
    static int PUERTO_SERVIDOR_3 = 60003;

    static class Worker extends Thread {
        String host;
        int port;
        double[][] Ad;
        double[][] B1d;
        double[][] B2d;
        double[][] B3d;
        double[][] C1d = new double[N/3][N/3];
        double[][] C2d = new double[N/3][N/3];
        double[][] C3d = new double[N/3][N/3];

        Worker(String host, int port, double[][] Ad, double[][] B1d, double[][] B2d, double[][] B3d) {
            this.host = host;
            this.port = port;
            this.Ad = Ad;
            this.B1d = B1d;
            this.B2d = B2d;
            this.B3d = B3d;
        }

        public void run() {
            try {
                //Socket socket = new Socket(host, port);
                Socket socket = null;
                for (; ; ) {
                    try {
                        socket = new Socket(host, port);
                        break;
                    } catch (Exception e) {
                        System.err.println(e.getMessage());
                    }
                }

                ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
                ObjectInputStream in = new ObjectInputStream(socket.getInputStream());

                // Envío de A y B al servidor
                out.writeObject(Ad);
                out.writeObject(B1d);
                out.writeObject(B2d);
                out.writeObject(B3d);

                // Recepción de las 3 matrices C del servidor
                double[][] C1a = (double[][]) in.readObject();
                this.C1d = C1a;
                double[][] C2a = (double[][]) in.readObject();
                this.C2d = C2a;
                double[][] C3a = (double[][]) in.readObject();
                this.C3d = C3a;

                // Cierre de conexiones
                socket.close();

            } catch (Exception e) {
                System.err.println(e.getMessage());
            }
        }

    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        System.out.print("Con qué nodo deseas trabajar? ");
        int nodo = sc.nextInt();
        sc.close();

        switch (nodo) {
            case 0:
                try {
                    double[][] A = new double[N][N];
                    double[][] B = new double[N][N];
                    double[][] C = new double[N][N];
                    // Inicialización de la matriz A
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < N; j++) {
                            A[i][j] = 2 * i + j;
                        }
                    }

                    // Inicialización de la matriz B y su transposición
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < N; j++) {
                            B[i][j] = 3 * i - j;
                        }
                    }
                    for (int i = 0; i < N; i++) {
                        for (int j = i + 1; j < N; j++) {
                            double temp = B[i][j];
                            B[i][j] = B[j][i];
                            B[j][i] = temp;
                        }
                    }
                    // División de las matrices A y B en 3 partes iguales
                    int partSize = N / 3;
                    double[][] A1 = new double[partSize][N];
                    double[][] A2 = new double[partSize][N];
                    double[][] A3 = new double[partSize][N];
                    double[][] B1 = new double[partSize][N];
                    double[][] B2 = new double[partSize][N];
                    double[][] B3 = new double[partSize][N];
                    for (int i = 0; i < partSize; i++) {
                        A1[i] = Arrays.copyOfRange(A, i, i + 1)[0];
                        A2[i] = Arrays.copyOfRange(A, i + partSize, i + partSize + 1)[0];
                        A3[i] = Arrays.copyOfRange(A, i + partSize * 2, i + partSize * 2 + 1)[0];
                        B1[i] = Arrays.copyOfRange(B, i, i + 1)[0];
                        B2[i] = Arrays.copyOfRange(B, i + partSize, i + partSize + 1)[0];
                        B3[i] = Arrays.copyOfRange(B, i + partSize * 2, i + partSize * 2 + 1)[0];
                    }

                    // Creación de los Workers y conexión a los servidores
                    Worker node1 = new Worker("20.25.113.127", PUERTO_SERVIDOR_1, A1, B1, B2, B3);
                    Worker node2 = new Worker("52.255.190.77", PUERTO_SERVIDOR_2, A2, B1, B2, B3);
                    Worker node3 = new Worker("52.152.224.83", PUERTO_SERVIDOR_3, A3, B1, B2, B3);

                    node1.start();
                    node1.join();
                    node2.start();
                    node2.join();
                    node3.start();
                    node3.join();
                    // Espera de resultados de los servidores
                    double[][] C1 = new double[partSize][partSize];
                    double[][] C2 = new double[partSize][partSize];
                    double[][] C3 = new double[partSize][partSize];
                    double[][] C4 = new double[partSize][partSize];
                    double[][] C5 = new double[partSize][partSize];
                    double[][] C6 = new double[partSize][partSize];
                    double[][] C7 = new double[partSize][partSize];
                    double[][] C8 = new double[partSize][partSize];
                    double[][] C9 = new double[partSize][partSize];
                    C1 = node1.C1d;
                    C2 = node1.C2d;
                    C3 = node1.C3d;
                    C4 = node2.C1d;
                    C5 = node2.C2d;
                    C6 = node2.C3d;
                    C7 = node3.C1d;
                    C8 = node3.C2d;
                    C9 = node3.C3d;

                    // Unión de las matrices C
                    for (int i = 0; i < partSize; i++) {
                        for (int j = 0; j < partSize; j++) {
                            C[i][j] = C1[i][j];
                            C[i][j+partSize] = C2[i][j];
                            C[i][j+2*partSize] = C3[i][j];
                            C[i+partSize][j] = C4[i][j];
                            C[i+partSize][j+partSize] = C5[i][j];
                            C[i+partSize][j+2*partSize] = C6[i][j];
                            C[i+2*partSize][j] = C7[i][j];
                            C[i+2*partSize][j+partSize] = C8[i][j];
                            C[i+2*partSize][j+2*partSize] = C9[i][j];
                        }
                    }
                    // Cálculo del checksum de la matriz C
                    double checksum = 0;
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < N; j++) {
                            checksum += C[i][j];
                        }
                    }
                    if (N == 12) {
                        System.out.println("Matriz A:");
                        imprimirMatriz(A);
                        System.out.println("Matriz B:");
                        imprimirMatriz(B);
                        System.out.println("Matriz C:");
                        imprimirMatriz(C);
                        System.out.println("El checksum de la matriz C es: " + checksum);
                    } else if (N == 3000) {
                        System.out.println("Checksum de la matriz C: " + checksum);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
                
                break;
            case 1:
                try {
                    int partSize = N / 3;
                    double[][] A1c = new double[partSize][N];
                    double[][] B1c = new double[partSize][N];
                    double[][] B2c = new double[partSize][N];
                    double[][] B3c = new double[partSize][N];
                    double[][] C1c = new double[partSize][partSize];
                    double[][] C2c = new double[partSize][partSize];
                    double[][] C3c = new double[partSize][partSize];
                    // Crear el socket del servidor
                    ServerSocket serverSocket = new ServerSocket(PUERTO_SERVIDOR_1);

                    // Esperar a que llegue una conexión
                    System.out.println("Esperando conexión en el puerto " + PUERTO_SERVIDOR_1 + "...");
                    Socket clientSocket = serverSocket.accept();
                    System.out.println("Conexión aceptada");

                    // Recibir la matriz A1
                    ObjectOutputStream oos = new ObjectOutputStream(clientSocket.getOutputStream());
                    ObjectInputStream ois = new ObjectInputStream(clientSocket.getInputStream());
                    A1c = (double[][]) ois.readObject();

                    // Recibir las tres partes de B
                    B1c = (double[][]) ois.readObject();
                    B2c = (double[][]) ois.readObject();
                    B3c = (double[][]) ois.readObject();

                    // Calcular las tres partes de C
                    C1c = multiplyMatrix(A1c, B1c);
                    C2c = multiplyMatrix(A1c, B2c);
                    C3c = multiplyMatrix(A1c, B3c);

                    // Enviar las tres partes de C al cliente
                    oos.writeObject(C1c);
                    oos.writeObject(C2c);
                    oos.writeObject(C3c);

                    // Cerrar la conexión
                    oos.close();
                    ois.close();
                    clientSocket.close();
                    serverSocket.close();
                } catch (Exception e) {
                    System.err.println("Error en servidor: " + e.getMessage());
                }
                break;
            case 2:
                try {
                    int partSize = N / 3;
                    double[][] A1c = new double[partSize][N];
                    double[][] B1c = new double[partSize][N];
                    double[][] B2c = new double[partSize][N];
                    double[][] B3c = new double[partSize][N];
                    double[][] C4c = new double[partSize][partSize];
                    double[][] C5c = new double[partSize][partSize];
                    double[][] C6c = new double[partSize][partSize];
                    // Crear el socket del servidor
                    ServerSocket serverSocket = new ServerSocket(PUERTO_SERVIDOR_2);

                    // Esperar a que llegue una conexión
                    System.out.println("Esperando conexión en el puerto " + PUERTO_SERVIDOR_2 + "...");
                    Socket clientSocket = serverSocket.accept();
                    System.out.println("Conexión aceptada");

                    // Recibir la matriz A1
                    System.out.println("Recibo la matriz A1");
                    ObjectOutputStream oos = new ObjectOutputStream(clientSocket.getOutputStream());
                    ObjectInputStream ois = new ObjectInputStream(clientSocket.getInputStream());
                    A1c = (double[][]) ois.readObject();

                    // Recibir las tres partes de B
                    System.out.println("Recibo las 3 de B");
                    B1c = (double[][]) ois.readObject();
                    B2c = (double[][]) ois.readObject();
                    B3c = (double[][]) ois.readObject();

                    // Calcular las tres partes de C
                    System.out.println("Calculo las 3 de C");
                    C4c = multiplyMatrix(A1c, B1c);
                    C5c = multiplyMatrix(A1c, B2c);
                    C6c = multiplyMatrix(A1c, B3c);

                    // Enviar las tres partes de C al cliente
                    System.out.println("Envio las 3 partes de C");
                    oos.writeObject(C4c);
                    oos.writeObject(C5c);
                    oos.writeObject(C6c);

                    // Cerrar la conexión
                    oos.close();
                    ois.close();
                    clientSocket.close();
                    serverSocket.close();
                } catch (Exception e) {
                    System.err.println("Error en servidor: " + e.getMessage());
                }
                break;
            case 3:
                try {
                    int partSize = N / 3;
                    double[][] A1c = new double[partSize][N];
                    double[][] B1c = new double[partSize][N];
                    double[][] B2c = new double[partSize][N];
                    double[][] B3c = new double[partSize][N];
                    double[][] C7c = new double[partSize][partSize];
                    double[][] C8c = new double[partSize][partSize];
                    double[][] C9c = new double[partSize][partSize];
                    // Crear el socket del servidor
                    ServerSocket serverSocket = new ServerSocket(PUERTO_SERVIDOR_3);

                    // Esperar a que llegue una conexión
                    System.out.println("Esperando conexión en el puerto " + PUERTO_SERVIDOR_3 + "...");
                    Socket clientSocket = serverSocket.accept();
                    System.out.println("Conexión aceptada");

                    // Recibir la matriz A1
                    System.out.println("Recibo la matriz A1");
                    ObjectOutputStream oos = new ObjectOutputStream(clientSocket.getOutputStream());
                    ObjectInputStream ois = new ObjectInputStream(clientSocket.getInputStream());
                    A1c = (double[][]) ois.readObject();

                    // Recibir las tres partes de B
                    System.out.println("Recibo las 3 de B");
                    B1c = (double[][]) ois.readObject();
                    B2c = (double[][]) ois.readObject();
                    B3c = (double[][]) ois.readObject();

                    // Calcular las tres partes de C
                    System.out.println("Calculo las 3 de C");
                    C7c = multiplyMatrix(A1c, B1c);
                    C8c = multiplyMatrix(A1c, B2c);
                    C9c = multiplyMatrix(A1c, B3c);

                    // Enviar las tres partes de C al cliente
                    System.out.println("Envio las 3 partes de C");
                    oos.writeObject(C7c);
                    oos.writeObject(C8c);
                    oos.writeObject(C9c);

                    // Cerrar la conexión
                    oos.close();
                    ois.close();
                    clientSocket.close();
                    serverSocket.close();
                } catch (Exception e) {
                    System.err.println("Error en servidor: " + e.getMessage());
                }
                break;
            default:
                System.out.println("El nodo ingresado no es válido");
                break;
        }
    }

    private static double[][] multiplyMatrix(double[][] Au, double[][] Bu) {
        double[][] Cx = new double[N/3][N/3];

        for (int i = 0; i < N/3; i++){
            for (int j = 0; j < N/3; j++){
                for (int k = 0; k < N; k++){
                    Cx[i][j] += Au[i][k] * Bu[j][k];
                }
            }
        }
        return Cx;
    }

    public static double[][] recibirMatriz(Socket socket, int size) throws IOException {
        double[][] matriz = new double[size][size];
        DataInputStream entrada = new DataInputStream(socket.getInputStream());

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matriz[i][j] = entrada.readDouble();
            }
        }

        return matriz;
    }

    public static void imprimirMatriz(double[][] matriz) {
        for (int i = 0; i < matriz.length; i++) {
            for (int j = 0; j < matriz[0].length; j++) {
                System.out.print(matriz[i][j] + "\t");
            }
            System.out.println();
        }
        System.out.println();
    }
}
