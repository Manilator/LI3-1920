package view;

import java.util.ArrayList;
import java.util.List;

import static Utils.Constants.N_BRANCHES;
import static Utils.Constants.N_MONTHS;

public class GestVendasView implements IGestVendasView {

    public GestVendasView() {
    }

    public void printMenu(){
        printMessage("! --------------------------------------------- !");
        printMessage("1  - Query 1  # Produtos nunca comprados");
        printMessage("2  - Query 2  # Total global de vendas & Compradores distintos");
        printMessage("3  - Query 3  # Informações mensais de um cliente");
        printMessage("4  - Query 4  # Informações mensais de um produto");
        printMessage("5  - Query 5  # Produtos mais comprados por um Cliente");
        printMessage("6  - Query 6  # Top produtos mais comprados");
        printMessage("7  - Query 7  # Top 3 clientes por filial");
        printMessage("8  - Query 8  # Top clientes que compraram produtos únicos");
        printMessage("9  - Query 9  # Top clientes de um produto");
        printMessage("10 - Query 10 # Faturação mensal de cada filial");
        printMessage("11 - Carregar dados");
        printMessage("12 - Guardar dados");
        printMessage("*  - Exit");
        printMessage("! --------------------------------------------- !");
    }

    void printSeparator()
    {
        printMessage("===========================");
    }

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

    public void printMessage(String message){
        System.out.println(message);
    }

    public void query3View(double[][] result) {
        for (int i=0;i < 12;i++) {
            printMessage(Integer.toString(i));
            printMessage("Numero Compras:"+ result[i][0]);
            printMessage("Produtos Distintos:"+ result[i][1]);
            printMessage("Valor total gasto:"+ result[i][2]);
            printMessage("------------------");
	      }
    }

    public void query4View(double[][] result) {
        for (int i = 0; i < N_MONTHS; i++) {
            printMessage("Mês " + String.valueOf(i+1));
            printMessage("Número de vendas: " + String.valueOf((int) result[i][0]));
            printMessage("Faturado: " + String.format("%.3f", result[i][1]));
            printMessage("Número de cliente: " + String.valueOf((int) result[i][2]));
        }
    }
  
    public void query5View(String[][] result) {
        for (String[] res : result)
            System.out.println(res[0] + " " + res[1]);
    }

    public void query6View(String[][] result) {
        List<String> list = new ArrayList<>();
        for(int i = 0; i < N_MONTHS; i++) {
            list.add("---- Produto " + result[i][0] + "\n" + "Quantidade: " + result[i][1] + "\n" + "Clientes distintos: " + result[i][2]);
        }
        Pages pages = new Pages(list.size(), list);
        pages.show(0);
    }

    public void query7View(String[][][] result) {
        for (int i = 0; i < N_BRANCHES; i++) {
            printMessage("---- Filial: " + String.valueOf(i+1));
            for (int j = 0; j < 3; j++) {
                printMessage("Codigo de cliente: " + result[i][j][0] + " | Faturado: " + String.format("%.1f", Double.parseDouble(result[i][j][1])));
            }
        }
    }

    public void cleanConsole()
    {
        printMessage("\033[H\033[2J");
        System.out.flush();
    }
}
