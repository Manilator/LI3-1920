package view;

import java.util.List;
import java.util.Map;

/**
 * Interface da classe principal da view do sistema
 */
public interface IGestVendasView {

    /**
     * Imprimir o menu
     */
    void printMenu();

    /**
     * Imprimir o menu de loadd
     */
    void printLoad();

    /**
     * Imprimir as escolhas de load
     */
     void loadChoice();

    /**
     * Imprime a mensagem fornecida
     * @param message Mensagem a ser impressa
     */
    void printMessage(String message);

    /**
     * Imprime a mensagem numa cor nao default
     * @param message Mensagem a ser impressa
     * @param color Cor escolhida
     */
    void printMessage(String message, String color);

    /**
     * Limpar o terminal
     */
    void cleanConsole();

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param list Matriz com os resultados a serem apresentados
     * @param n_page Número da página a mostrar
     */
    void query1View(List<String> list, int n_page);

    /**
     * Função responsável por mostrar o resultado da query 2 ao utilizador
     * @param list Lista com os resultados a serem apresentados
     */
    void query2View(List<Integer> list);

    /**
     * Função responsável por mostrar o resultado da query 3 ao utilizador
     * @param result Matriz com os resultados a serem apresentados
     * @param client Código de cliente ao qual os resultados estão associados
     */
    void query3View(double[][] result, String client);
    
    /**
     * Função responsável por mostrar o resultado da query 4 ao utilizador
     * @param result Matriz com os resultados a serem apresentados
     * @param product Código de produto ao qual os resultados estão associados
     */
    void query4View(double[][] result, String product);

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param list Matriz com os resultados a serem apresentados
     * @param client Código de cliente ao qual os resultados estão associados
     * @param n_page Número da página a mostrar
     */
    void query5View(List<String> list, int n_page, String client);

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param list Matriz com os resultados a serem apresentados
     * @param n_page Número da página a mostrar
     */
    void query6View(List<String> list, int n_page);

    /**
     * Função responsável por mostrar o resultado da query 6 ao utilizador
     * @param result Matriz com os resultados a serem apresentados
     */
    void query7View(String[][][] result);

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param list Matriz com os resultados a serem apresentados
     * @param n_page Número da página a mostrar
     */
    void query8View(List<String> list, int n_page);

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param list Matriz com os resultados a serem apresentados
     * @param n_page Número da página a mostrar
     * @param product Código de produto ao qual os resultados estão associados
     */
    void query9View(List<String> list, int n_page, String product);

    /**
     * Função responsável por mostrar o resultado da query 10 ao utilizador
     * @param result Hashmap com os códigos e a matriz com os resultados a serem apresentados
     * @param product Código de produto ao qual os resultados estão associados
     */
    void query10View(Map<String, double[][]> result, String product);

    /**
     * Função responsável por mostrar o resultado da query estatistica 1 ao utilizador
     * @param statisticalConsult Array com os resultados a serem apresentados
     */
    void queryE1View(String[] statisticalConsult);

    /**
     * Função responsável por mostrar o resultado da query 10 ao utilizador
     * @param result Array com os primeiros resultados a serem apresentados
     * @param result2 Array com os segundos resultados a serem apresentados
     * @param result3 Array com os terceiros resultados a serem apresentados
     */
    void queryE2View(int[][] result, int[][] result2, double[][] result3);
}
