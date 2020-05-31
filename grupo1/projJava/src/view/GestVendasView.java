package view;

import java.util.Arrays;
import java.util.List;
import java.util.Map;

import static Utils.Constants.*;

/**
 * Classe principal da view do sistema
 */
public class GestVendasView implements IGestVendasView {

    public static final String ANSI_RESET = "\u001B[0m" ;
    public static final String ANSI_BLACK = "\u001B[30m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_WHITE = "\u001B[37m";

    /**
     * Contrutor vazio da classe
     */
    public GestVendasView() {
    }

    /**
     * Imprimir o menu
     */
    public void printMenu(){
        printMessage("! --------------------------------------------- !",CYAN);
        printMessage("1  - [I] Query 1  # Produtos nunca comprados",CYAN);
        printMessage("2  - [I] Query 2  # Total global de vendas & Compradores distintos",CYAN);
        printMessage("3  - [I] Query 3  # Informações mensais de um cliente",CYAN);
        printMessage("4  - [I] Query 4  # Informações mensais de um produto",CYAN);
        printMessage("5  - [I] Query 5  # Produtos mais comprados por um Cliente",CYAN);
        printMessage("6  - [I] Query 6  # Top produtos mais comprados",CYAN);
        printMessage("7  - [I] Query 7  # Top 3 clientes por filial",CYAN);
        printMessage("8  - [I] Query 8  # Top clientes que compraram produtos únicos",CYAN);
        printMessage("9  - [I] Query 9  # Top clientes de um produto",CYAN);
        printMessage("10 - [I] Query 10 # Faturação mensal de cada filial",CYAN);
        printMessage("11 - [E] Query 1 # Dados referentes á ultima leitura",CYAN);
        printMessage("12 - [E] Query 2 # Dados gerais atuais já registados nas estruturas",CYAN);
        printMessage("13 - Carregar dados",CYAN);
        printMessage("14 - Guardar dados",CYAN);
        printMessage("*  - Exit",CYAN);
        printMessage("! --------------------------------------------- !",CYAN);
    }

    /**
     * Imprimir o menu de load
     */
    public void printLoad() {
        printMessage("1 - Carregar dados (linhas)");
        printMessage("2 - Carregar dados (.dat)");
        printMessage("3 - Limpar dados");
    }

    /**
     * Imprimir as escolhas de load
     */
    public void loadChoice() {
        printMessage("1 - Clientes");
        printMessage("2 - Produtos");
        printMessage("3 - Vendas");
    }

    /**
     * Imprime a mensagem fornecida
     * @param message Mensagem a ser impressa
     */
    public void printMessage(String message){
        System.out.println(message);
    }

    /**
     * Imprime a mensagem fornecida
     * @param message Mensagem a ser impressa
     */
    public void printMessage(String message, String color){
        String finalColor;
        switch (color){
            case "black" -> finalColor = ANSI_BLACK;
            case "red" -> finalColor = ANSI_RED;
            case "green" -> finalColor = ANSI_GREEN;
            case "yellow" -> finalColor = ANSI_YELLOW;
            case "blue" -> finalColor = ANSI_BLUE;
            case "purple" -> finalColor = ANSI_PURPLE;
            case "cyan" -> finalColor = ANSI_CYAN;
            case "white" -> finalColor = ANSI_WHITE;
            default -> finalColor = ANSI_RESET;
        }
        System.out.println(finalColor + message + ANSI_RESET);
    }

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param list Matriz com os resultados a serem apresentados
     * @param n_page Número da página a mostrar
     */
    public void query1View(List<String> list, int n_page) {
        printMessage("==================================");
        printMessage("#### Produtos nunca comprados ####");
        printMessage("==================================");
        IPages pages = new Pages(list.size(), ELEMENTS_PER_PAGE, list);
        pages.show(n_page);
        pages.choices();
    }

    /**
     * Função responsável por mostrar o resultado da query 2 ao utilizador
     * @param list Lista com os resultados a serem apresentados
     */
    public void query2View(List<Integer> list) {
        int[] total = new int[2];
        Arrays.fill(total,0);
        int i = 0;
        for (int j = 1; i < N_BRANCHES*2; i++, j++) {
            printMessage("---- Filial " + j);
            printMessage("Número distinto de clientes: " + list.get(i++));
            total[1] += list.get(i);
            printMessage("Número de vendas:            " + list.get(i));
        }
        total[0] = list.get(i);
        printMessage("---- Total ");
        printMessage("Total clientes distintos:    " + total[0]);
        printMessage("Total vendas:                " + total[1]);
    }

    /**
     * Função responsável por mostrar o resultado da query 3 ao utilizador
     * @param result Matriz com os resultados a serem apresentados
     * @param client Código de cliente ao qual os resultados estão associados
     */
    public void query3View(double[][] result, String client) {
        ITable table = new Table();
        table.table3View(result, client);
    }

    /**
     * Função responsável por mostrar o resultado da query 4 ao utilizador
     * @param result Matriz com os resultados a serem apresentados
     * @param product Código de produto ao qual os resultados estão associados
     */
    public void query4View(double[][] result, String product) {
        ITable table = new Table();
        table.table4View(result, product);
    }

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param list Matriz com os resultados a serem apresentados
     * @param client Código de cliente ao qual os resultados estão associados
     * @param n_page Número da página a mostrar
     */
    public void query5View(List<String> list, int n_page, String client) {
        printMessage("=================================");
        printMessage("### Produtos que mais comprou ###");
        printMessage("###       Cliente " + client + "       ###");
        printMessage("=================================");
        IPages pages = new Pages(list.size(),ELEMENTS_PER_PAGE,list);
        pages.show(n_page);
        pages.choices();
    }

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param list Matriz com os resultados a serem apresentados
     * @param n_page Número da página a mostrar
     */
    public void query6View(List<String> list, int n_page) {
        printMessage("================================");
        printMessage("###       Top Produtos       ###");
        printMessage("================================");
        IPages pages = new Pages(list.size(),3,list);
        pages.show(n_page);
        pages.choices();
    }

    /**
     * Função responsável por mostrar o resultado da query 6 ao utilizador
     * @param result Matriz com os resultados a serem apresentados
     */
    public void query7View(String[][][] result) {
        for (int i = 0; i < N_BRANCHES; i++) {
            printMessage("---- Filial: " + String.valueOf(i+1));
            for (int j = 0; j < 3; j++) {
                printMessage("Codigo de cliente: " + result[i][j][0] + " | Faturado: " + String.format("%.1f", Double.parseDouble(result[i][j][1])));
            }
        }
    }

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param list Matriz com os resultados a serem apresentados
     * @param n_page Número da página a mostrar
     */
    public void query8View(List<String> list, int n_page) {
        printMessage("================================");
        printMessage("###       Top Clientes       ###");
        printMessage("###      PRODUTOS ÚNICOS     ###");
        printMessage("================================");
        IPages pages = new Pages(list.size(),ELEMENTS_PER_PAGE,list);
        pages.show(n_page);
        pages.choices();
    }

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param list Matriz com os resultados a serem apresentados
     * @param n_page Número da página a mostrar
     * @param product Código de produto ao qual os resultados estão associados
     */
    public void query9View(List<String> list, int n_page, String product) {
        printMessage("=================================");
        printMessage("###       Top Clientes        ###");
        printMessage("###      Produto " + product + "       ###");
        printMessage("=================================");
        IPages pages = new Pages(list.size(),ELEMENTS_PER_PAGE,list);
        pages.show(n_page);
        pages.choices();
    }

    /**
     * Função responsável por mostrar o resultado da query 10 ao utilizador
     * @param result Hashmap com os códigos e a matriz com os resultados a serem apresentados
     * @param product Código de produto ao qual os resultados estão associados
     */
    public void query10View(Map<String, double[][]> result, String product){
        ITable table = new Table();
        printMessage("---- Produto " + product);
        table.tableE2View(result.get(product));
        printMessage("(Caso pretenda voltar ao menu, insira qualquer carater)");
    }

    /**
     * Função responsável por mostrar o resultado da query estatistica 1 ao utilizador
     * @param statisticalConsult Array com os resultados a serem apresentados
     */
    public void queryE1View(String[] statisticalConsult) {
        printMessage("Nome do ficheiro: " + statisticalConsult[0]);
        printMessage("Vendas inválidas: " + statisticalConsult[1]);
        printMessage("Total de Produtos: " + statisticalConsult[2]);
        printMessage("Total Produtos distintos comprados: " + statisticalConsult[3]);
        printMessage("Total Produtos distintos não comprados: " + statisticalConsult[4]);
        printMessage("Total de Clientes: " + statisticalConsult[5]);
        printMessage("Total de Clientes que compraram: " + statisticalConsult[6]);
        printMessage("Total de Clientes que não compraram: " + statisticalConsult[7]);
        printMessage("Total de compras com valor igual a 0: " + statisticalConsult[8]);
        printMessage("Faturação total: " + statisticalConsult[9]);
    }

    /**
     * Função responsável por mostrar o resultado da query 10 ao utilizador
     * @param result Array com os primeiros resultados a serem apresentados
     * @param result2 Array com os segundos resultados a serem apresentados
     * @param result3 Array com os terceiros resultados a serem apresentados
     */
    public void queryE2View(int[][] result, int[][] result2, double[][] result3) {
        ITable table = new Table();
        printMessage("\n---- Número de distintos clientes que compraram por mês filial a filial: ");
        table.tableE2View(result);
        printMessage("\n---- Número total de compras por mês: ");
        table.tableE2View(result2);
        printMessage("\n---- Faturação total por mês filial a filial: ");
        table.tableE2View(result3);
    }

    /**
     * Limpar o terminal
     */
    public void cleanConsole()
    {
        printMessage("\033[H\033[2J");
        System.out.flush();
    }
}
