import controller.IGestVendasController;
import controller.GestVendasController;
import view.GestVendasView;

import java.io.IOException;

/**
 * Classe que inicializa a execucao do programa
 */
public class GestVendasAppMVC {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        GestVendasView view = new GestVendasView();
        view.printMessage("Loading data...");

        IGestVendasController controller;

        if (args.length == 0)
            controller = new GestVendasController();
        else
            controller = new GestVendasController(args[0],args[1],args[2]);
        controller.startController();
    }
}
