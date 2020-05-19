import controller.IGestVendasController;
import controller.GestVendasController;

import java.io.IOException;

public class GestVendasAppMVC {
    public static void main(String[] args) throws IOException {
        System.out.println("Loading data...");

        IGestVendasController controller = new GestVendasController();

        if (args.length == 0) {
            controller.startController();
        }
    }
}
