import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class ServidorRMI {
    public static void main(String[] args) throws Exception {
        Registry registry = LocateRegistry.createRegistry(1099);
        String url = "rmi://localhost/prueba";
        MatricesRMI obj = new MatricesRMI();
        // Registra la instancia en el rmiregistry
        Naming.rebind(url, obj);
    }
}