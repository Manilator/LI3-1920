package view;

public class View {

    public View() {
    }

    public void printMenu(){
        System.out.println("! --------------- !");
        System.out.println("1  - Query 1");
        System.out.println("2  - Query 2");
        System.out.println("3  - Query 3");
        System.out.println("4  - Query 4");
        System.out.println("5  - Query 5");
        System.out.println("6  - Query 6");
        System.out.println("7  - Query 7");
        System.out.println("8  - Query 8");
        System.out.println("9  - Query 9");
        System.out.println("10 - Query 10");
        System.out.println("11 - Query 11");
        System.out.println("12 - Query 12");
        System.out.println("13 - Query 13");
        System.out.println("*  - Exit");
        System.out.println("! --------------- !");
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
}
