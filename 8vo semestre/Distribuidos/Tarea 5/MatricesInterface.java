import java.rmi.Remote;
import java.rmi.RemoteException;

public interface MatricesInterface extends Remote {
    public float[][] multiplica_matrices(float[][] A, float[][] B) throws RemoteException;
}

