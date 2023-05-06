import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class MatricesRMI extends UnicastRemoteObject implements MatricesInterface {

    public MatricesRMI() throws RemoteException {
        super();
    }

    public float[][] multiplica_matrices(float[][] A, float[][] B) throws RemoteException {
        int n = A.length; // filas de A
        int m = B[0].length; // columnas de B
        int p = B.length; // filas de B
    //     System.out.println("El valor de n es:"+n);
    //     System.out.println("El valor de m es:"+m);
    //     System.out.println("El valor de p es:"+p);
    //     System.out.println("Imprimimos el A");
    //     for(int q=0;q< n;q++){
    //        for(int j=0;j<m;j++){
    //         System.out.printf("%.2f\t",A[q][j]);
    //        }
    //        System.out.println("\n");
    //    }
    //    System.out.println("Ahora Imprimimos el BT");
    //    for(int q=0;q< n;q++){
    //        for(int j=0;j<m;j++){
    //         System.out.printf("%.2f\t",B[q][j]);
    //        }
    //        System.out.println("\n");
    
    //     }
        float[][] C = new float[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                float sum = 0.0f;
                for (int k = 0; k < m; k++) {
                    //System.out.println("Estoy multiplicando en A:"+A[i][k]+"* B que es:"+B[j][k]);
                    //System.out.println("\n");
                    sum += A[i][k] * B[j][k];
                }
                C[i][j] = sum;
            }
        }
        // System.out.println("Se obtuvo la matriz C resultado: ");
        // for(int q=0;q< n;q++){
        //     for(int j=0;j<n;j++){
        //      System.out.printf("%.2f\t",C[q][j]);
        //     }
        //     System.out.println("\n");
        // }
        return C;
    }
}


