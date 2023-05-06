import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Arrays;

import java.rmi.RemoteException;
import java.rmi.*;

public class ClienteRMI {

    private static final int N = 9;
    private static final int M = 4;
    private static final int P = 9;
    private static final int NUM_HILOS = 81;
    private static float[][][] C = new float[81][N / P][N / P];

    private static class Worker extends Thread {
        private MatricesInterface matrices;
        private float[][] A;
        private float[][] BT;
        private int inicio;
        private float[][][] C;

        public Worker(MatricesInterface matrices, float[][] A, float[][] BT, int inicio, float[][][] C) {
            this.matrices = matrices;
            this.A = A;
            this.BT = BT;
            this.inicio = inicio;
            this.C = C;
        }

        public void run() {
            try {
                C[inicio] = matrices.multiplica_matrices(A, BT);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }

    }

    public static void main(String[] args) {
        try {
            // Obtenemos el registro RMI
            // Registry registro = LocateRegistry.getRegistry("localhost", 1099);

            MatricesInterface matrices1 = (MatricesInterface) Naming.lookup("rmi://localhost/prueba");
            MatricesInterface matrices2 = (MatricesInterface) Naming.lookup("rmi://10.0.0.5/prueba");
            //MatricesInterface matrices2 = (MatricesInterface) Naming.lookup("rmi://localhost/prueba");
            MatricesInterface matrices3 = (MatricesInterface) Naming.lookup("rmi://10.0.0.6/prueba");
            //MatricesInterface matrices3 = (MatricesInterface) Naming.lookup("rmi://localhost/prueba");

            // Inicializamos las matrices A y B
            float[][] A = new float[N][M];
            float[][] B = new float[M][N];
            float[][] BT = new float[N][M];
            inicializar_matrices(A, B);

            // Calculamos la transpuesta de B
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    BT[j][i] = B[i][j];
                }
            }

            // Dividir matrices A y BT en 9 partes y guardarlas en arreglos
            float[][][] partesA = dividirMatriz(A, N, M);
            float[][][] partesB = dividirMatriz(BT, N, M);
            
            Worker[] workers = new Worker[NUM_HILOS];
            int inicio = 0;
            for (int j = 0; j < P; j++) {
                for (int k = 0; k < P; k++) {
                    
                    if (inicio < 26) {
                        workers[inicio] = new Worker(matrices1, partesA[j], partesB[k], inicio, C);
                    }

                    else if (inicio > 26 && inicio < 53) {
                        workers[inicio] = new Worker(matrices2, partesA[j], partesB[k], inicio, C);
                    }

                    else {
                        workers[inicio] = new Worker(matrices3, partesA[j], partesB[k], inicio, C);
                    }

                    workers[inicio].start();
                    inicio++;
                    }
            }

            for(int i = 0; i < workers.length; i++){
                workers[i].join();
            }

            float Cres[][] = unirMatrices(C);
            if(N == P){
                System.out.println("Se obtuvo la matriz C resultado: ");
                for(int q=0;q< N;q++){
                    for(int j=0;j<N;j++){
                        System.out.printf("%.2f\t",Cres[q][j]);
                    }
                    System.out.println();
                }
            }
            double checksum = 0;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    checksum+= Cres[i][j];
                }
            }
            System.out.println("Checksum de la matriz = " + checksum);

        } catch (Exception e) {
            System.err.println("Excepción del cliente: " + e.toString());
            e.printStackTrace();
        }
    }

    public static void inicializar_matrices(float[][] A, float[][] B) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                A[i][j] = (float) 2 * i + 3 * j;
            }
        }
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                B[i][j] = (float) 3 * i - 2 * j;
            }
        }
    }

    public static float[][] unirMatrices(float[][][] matrices) {
        int n = matrices.length;
        int subMatrizSize = N / 9; 
        float[][] resultado = new float[N][N];
    
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < subMatrizSize; j++) {
                for (int k = 0; k < subMatrizSize; k++) {
                    int fila = (i / 9) * subMatrizSize + j; // Calcular la fila en la matriz resultado
                    int col = (i % 9) * subMatrizSize + k; // Calcular la columna en la matriz resultado
                    resultado[fila][col] = matrices[i][j][k]; // Asignar el valor de matrices[i][j][k] a la matriz resultado en la posición adecuada
                }
            }
        }
    
        return resultado;
    }
    

    // Método para dividir una matriz en 9 partes de tamaño N/9 x M
    public static float[][][] dividirMatriz(float[][] matriz, int N, int M) {
        int subMatrizSize = N / 9; // Tamaño de las submatrices
        float[][][] subMatrices = new float[9][subMatrizSize][M]; // Crear arreglo para almacenar las submatrices
    
        // Recorrer la matriz y dividirla en submatrices
        for (int i = 0; i < N; i++) {
            int subMatrizIndex = i / subMatrizSize; // Calcular el índice de la submatriz correspondiente
            int subMatrizRow = i % subMatrizSize; // Calcular la fila en la submatriz correspondiente
            for (int j = 0; j < M; j++) {
                subMatrices[subMatrizIndex][subMatrizRow][j] = matriz[i][j]; // Asignar el valor de la matriz original a la submatriz correspondiente
            }
        }
    
        return subMatrices;
    }
}