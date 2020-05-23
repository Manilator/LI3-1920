package view;

import java.util.List;

public interface IGestVendasView {

    void printMenu();

    void printMessage(String message);

    void cleanConsole();

    void query3View(double[][] result);

    void query4View(double[][] result);

    void query5View(String[][] result);

    void query6View(String[][] result);
}
