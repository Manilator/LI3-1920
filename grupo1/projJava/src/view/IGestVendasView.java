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
     * @param list Lista com os resultados a serem apresentados
     */
    void query2View(List<Integer> list);

    /**
     * Função responsável por mostrar o resultado da query 3 ao utilizador
     * @param result Matriz com os resultados a serem apresentados
     */
    void query3View(double[][] result);
    /**
     * Função responsável por mostrar o resultado da query 4 ao utilizador
     * @param result Matriz com os resultados a serem apresentados
     */
    void query4View(double[][] result);

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param result Matriz com os resultados a serem apresentados
     */
    void query5View(String[][] result);

    /**
     * Função responsável por mostrar o resultado da query 6 ao utilizador
     * @param result Matriz com os resultados a serem apresentados
     */
    void query7View(String[][][] result);

    /**
     * Função responsável por mostrar o resultado da query 10 ao utilizador
     * @param result Hashmap com os códigos e a matriz com os resultados a serem apresentados
     */
    void query10View(Map<String, double[][]> result);

    /**
     * Função responsável por mostrar o resultado da query estatistica 1 ao utilizador
     * @param statisticalConsult Array com os resultados a serem apresentados
     */
    void queryE1View(String[] statisticalConsult);
}
