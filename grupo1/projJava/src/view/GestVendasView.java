package view;

import java.util.Arrays;
import java.util.List;
import java.util.Map;

import static Utils.Constants.N_BRANCHES;
import static Utils.Constants.N_MONTHS;

public class GestVendasView implements IGestVendasView {

    public GestVendasView() {
    }

    /**
     * Imprimir o menu
     */
    public void printMenu(){
        printMessage("! --------------------------------------------- !");
        printMessage("1  - [I] Query 1  # Produtos nunca comprados");
        printMessage("2  - [I] Query 2  # Total global de vendas & Compradores distintos");
        printMessage("3  - [I] Query 3  # Informações mensais de um cliente");
        printMessage("4  - [I] Query 4  # Informações mensais de um produto");
        printMessage("5  - [I] Query 5  # Produtos mais comprados por um Cliente");
        printMessage("6  - [I] Query 6  # Top produtos mais comprados");
        printMessage("7  - [I] Query 7  # Top 3 clientes por filial");
        printMessage("8  - [I] Query 8  # Top clientes que compraram produtos únicos");
        printMessage("9  - [I] Query 9  # Top clientes de um produto");
        printMessage("10 - [I] Query 10 # Faturação mensal de cada filial");
        printMessage("11 - [E] Query 1 # Dados referentes á ultima leitura");
        printMessage("12 - [E] Query 2 # Dados gerais atuais já registados nas estruturas");
        printMessage("13 - Carregar dados");
        printMessage("14 - Guardar dados");
        printMessage("*  - Exit");
        printMessage("! --------------------------------------------- !");
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
     * Imprimir um separador
     */
    void printSeparator()
    {
        printMessage("===========================");
    }

    /**
     * Imprimir os valores de carregamento da base de dados
     */
    public void viewPrintStartValues(String clients_path, String products_path, String sales_path, int valid_clients, int valid_products, int valid_sales, int clients_read, int products_read, int sales_read) {
        printSeparator();
        printMessage("Path Clients: " + clients_path);
        printMessage("Path Products: " + products_path);
        printMessage("Path Sales: " + sales_path);
        printMessage("Clientes válidos: " + valid_clients);
        printMessage("Produtos válidos: " + valid_products);
        printMessage("Vendas válidas: " + valid_sales);
        printMessage("Clientes lidos: " + clients_read);
        printMessage("Produtos lidos: " + products_read);
        printMessage("Vendas lidas: " + sales_read);
        printSeparator();
    }

    /**
     * Imprime a mensagem fornecida
     * @param message Mensagem a ser impressa
     */
    public void printMessage(String message){
        System.out.println(message);
    }

    /**
     * Função responsável por mostrar o resultado da query 2 ao utilizador
     * @param list (!!!)
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
     * @param result (!!!)
     */
    public void query3View(double[][] result) {
        for (int i=0;i < 12;i++) {
            printMessage(Integer.toString(i));
            printMessage("Numero Compras:"+ result[i][0]);
            printMessage("Produtos Distintos:"+ result[i][1]);
            printMessage("Valor total gasto:"+ result[i][2]);
            printMessage("------------------");
	      }
    }

    /**
     * Função responsável por mostrar o resultado da query 4 ao utilizador
     * @param result (!!!)
     */
    public void query4View(double[][] result) {
        for (int i = 0; i < N_MONTHS; i++) {
            printMessage("Mês " + String.valueOf(i+1));
            printMessage("Número de vendas: " + String.valueOf((int) result[i][0]));
            printMessage("Faturado: " + String.format("%.3f", result[i][1]));
            printMessage("Número de cliente: " + String.valueOf((int) result[i][2]));
        }
    }

    /**
     * Função responsável por mostrar o resultado da query 5 ao utilizador
     * @param result (!!!)
     */
    public void query5View(String[][] result) {
        for (String[] res : result)
            System.out.println(res[0] + " " + res[1]);
    }

    /**
     * Função responsável por mostrar o resultado da query 7 ao utilizador
     * @param result (!!!)
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
     * Função responsável por mostrar o resultado da query 10 ao utilizador
     * @param result (!!!)
     */
    public void query10View(Map<String, double[][]> result){
    }

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
     * Limpar o terminal
     */
    public void cleanConsole()
    {
        printMessage("\033[H\033[2J");
        System.out.flush();
    }
}
