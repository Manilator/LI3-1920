package view;

import java.util.List;

public interface IGestVendasView {

    public void printMenu();

    public void printMessage(String message);

    public void cleanConsole();

    void query3View(double[][] result);

    public void query4View(double[][] result);

    public void query6View(String[][] result);
  
    public void query7View(String[][][] result);
}
