import controller.IGestVendasController;
import controller.GestVendasController;
import view.GestVendasView;

import java.io.IOException;

import static Utils.Constants.RED;

/**
 * Classe que inicializa a execucao do programa
 */
public class GestVendasAppMVC {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        GestVendasView view = new GestVendasView();
        view.cleanConsole();
        view.printMessage("Loading data...");

        IGestVendasController controller;
        try {
            if (args.length == 0)
                controller = new GestVendasController();
            else
                controller = new GestVendasController(args[0],args[1],args[2]);
            controller.startController();
        } catch (Exception e) {
            view.printMessage("Ocorreu um erro, verifique se os ficheiros iniciais se encontram no local correto. Terminando o programa...", RED);
        }

    }
}
