package view;

import java.util.List;
import java.util.Map;

public interface IGestVendasView {

    /**
     * Imprimir o menu
     */
    void printMenu();

    /**
     * Imprimir o menu de loadd
     */
    public void printLoad();

    /**
     * Imprimir as escolhas de load
     */
    public void loadChoice();

    /**
     * Imprime a mensagem fornecida
     * @param message Mensagem a ser impressa
     */
    void printMessage(String message);

    /**
     * Limpar o terminal
     */
    void cleanConsole();

    /**
     * Função responsável por mostrar o resultado da query 2 ao utilizador
     * @param list (!!!)
     */
    void query2View(List<Integer> list);

    /**
     * Função responsável por mostrar o resultado da query 3 ao utilizador
     * @param result (!!!)
     */
    void query3View(double[][] result);
    /**
     * Função responsável por mostrar o resultado da query 4 ao utilizador
     * @param result (!!!)
     */
    void query4View(double[][] result);

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param result (!!!)
     */
    void query5View(String[][] result);

    /**
     * Função responsável por mostrar o resultado da query 6 ao utilizador
     * @param result (!!!)
     */

    void query7View(String[][][] result);


    /**
     * Função responsável por mostrar o resultado da query 10 ao utilizador
     * @param result (!!!)
     */
    void query10View(Map<String, double[][]> result);

    void queryE1View(String[] statisticalConsult);
}
