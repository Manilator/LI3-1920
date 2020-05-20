package view;

import java.util.List;

import static Utils.Constants.N_BRANCHES;
import static Utils.Constants.N_MONTHS;

public class GestVendasView implements IGestVendasView {

    public GestVendasView() {
    }

    public void printMenu(){
        System.out.println("! --------------------------------------------- !");
        System.out.println("1  - Query 1  # Produtos nunca comprados");
        System.out.println("2  - Query 2  # Total global de vendas & Compradores distintos");
        System.out.println("3  - Query 3  # Informações mensais de um cliente");
        System.out.println("4  - Query 4  # Informações mensais de um produto");
        System.out.println("5  - Query 5  # Produtos mais comprados por um Cliente");
        System.out.println("6  - Query 6  # Top produtos mais comprados");
        System.out.println("7  - Query 7  # Top 3 clientes por filial");
        System.out.println("8  - Query 8  # Top clientes que compraram produtos únicos");
        System.out.println("9  - Query 9  # Top clientes de um produto");
        System.out.println("10 - Query 10 # Faturação mensal de cada filial");
        System.out.println("11 - Carregar dados");
        System.out.println("12 - Guardar dados");
        System.out.println("*  - Exit");
        System.out.println("! --------------------------------------------- !");
    }

    void printSeparator()
    {
        System.out.println("===========================");
    }

    public void viewPrintStartValues(String clients_path, String products_path, String sales_path, int valid_clients, int valid_products, int valid_sales, int clients_read, int products_read, int sales_read) {
        printSeparator();
        System.out.println("Path Clients: " + clients_path);
        System.out.println("Path Products: " + products_path);
        System.out.println("Path Sales: " + sales_path);
        System.out.println("Clientes válidos: " + valid_clients);
        System.out.println("Produtos válidos: " + valid_products);
        System.out.println("Vendas válidas: " + valid_sales);
        System.out.println("Clientes lidos: " + clients_read);
        System.out.println("Produtos lidos: " + products_read);
        System.out.println("Vendas lidas: " + sales_read);
        printSeparator();
    }

    public void printMessage(String message){
        System.out.println(message);
    }

    public void query4View(double[][] result) {
        for (int i = 0; i < N_MONTHS; i++) {
            printMessage("Mês " + String.valueOf(i+1));
            printMessage("Número de vendas: " + String.valueOf((int) result[i][0]));
            printMessage("Faturado: " + String.format("%.3f", result[i][1]));
            printMessage("Número de cliente: " + String.valueOf((int) result[i][2]));
        }
    }

    public void cleanConsole()
    {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }
}
