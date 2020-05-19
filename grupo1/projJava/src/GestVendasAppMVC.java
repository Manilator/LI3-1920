import controller.GestVendasController;
import controller.IGestVendasController;

import java.io.IOException;

public class GestVendasAppMVC {
    public static void main(String[] args) throws IOException {
        System.out.println("Starting Main!\n----------");

        IGestVendasController controller = new GestVendasController();

        if (args.length == 0) {
            controller.startController();
        }
        System.out.println("Closing Main!\n----------");
    }
}
