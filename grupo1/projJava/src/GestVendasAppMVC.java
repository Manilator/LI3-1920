import controller.IGestVendasController;
import controller.GestVendasController;

import java.io.IOException;

public class GestVendasAppMVC {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        System.out.println("Loading data...");

        IGestVendasController controller;

        if (args.length == 0)
            controller = new GestVendasController();
        else
            controller = new GestVendasController(args[0],args[1],args[2]);
        controller.startController();
    }
}
