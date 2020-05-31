package view;

import java.util.Arrays;
import java.util.List;
import java.util.Map;

import static Utils.Constants.*;

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
