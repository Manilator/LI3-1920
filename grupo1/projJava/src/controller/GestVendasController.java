package controller;

import model.GestVendasModel;
import model.IGestVendasModel;
import view.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

import static Utils.Constants.N_BRANCHES;

public class GestVendasController implements IGestVendasController {
    public IGestVendasView view;
    private final IGestVendasModel gv;
    private final BufferedReader in;
    private IPages pages;


    /**
     * Construtor do controller
     */
    public GestVendasController() {
        this.view = new GestVendasView();
        long startTime = System.nanoTime();
        this.gv = new GestVendasModel();
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        view.printMessage(String.valueOf("Clientes válidos: " + this.gv.getClientsSize()));
        view.printMessage(String.valueOf("Clientes lidos: " + this.gv.getReadClients()));
        view.printMessage(String.valueOf("Produtos válidos: " + this.gv.getProductsSize()));
        view.printMessage(String.valueOf("Produtos lidos: " + this.gv.getReadProducts()));
        view.printMessage(String.valueOf("Vendas válidos: " + this.gv.getValidSales()));
        view.printMessage(String.valueOf("Vendas lidas: " + this.gv.getReadSales()));
        in = new BufferedReader(new InputStreamReader(System.in));
    }

    /**
     * Função que inicia o controller
     * @throws IOException Exceção se ocorrer erros ao ler os ficheiros
     */
    public void startController() throws IOException {
        menu();
    }


    /**
     * Função que trata do controller da query 1
     */
    private void query1Controller() throws IOException {
        int n_page = 0;
        long startTime = System.nanoTime();
        List<String> list = gv.getProductNeverBought();
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        String choice = "-1";
        while(!choice.equals("0")) {
            view.printMessage("==================================");
            view.printMessage("#### Produtos nunca comprados ####");
            view.printMessage("==================================");
            pages = new Pages(list.size(),list);
            pages.show(n_page);
            pages.choices();
            choice = null;
            choice = in.readLine();
            view.printMessage("teste");
            if (choice.equals("n")) {
                view.printMessage(choice);
                n_page++;
            }
            else if(choice.equals("p")) {
                view.printMessage(choice);
                n_page--;
            }
            else if(choice.equals("c")) {
                view.printMessage(choice);
                view.printMessage("Número da página: ");
                n_page = Integer.parseInt((in.readLine()));
            } else
                choice = "0";
        }
    }

    /**
     * Função que trata do controller da query 2
     */
    private void query2Controller() throws IOException {
        int month = 0;
        view.printMessage("Insira o mês:");
        while(month < 1 || month > 12) {
            month = Integer.parseInt(in.readLine());
        }
        long startTime = System.nanoTime();
        List<Integer> list = gv.query2(month);
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        int[] total = new int[2];
        Arrays.fill(total,0);
        int i = 0;
        for (int j = 1; i < N_BRANCHES*2; i++, j++) {
            view.printMessage("---- Filial " + String.valueOf(j));
            view.printMessage("Número distinto de clientes: " + String.valueOf(list.get(i++)));
            total[1] += list.get(i);
            view.printMessage("Número de vendas:            " + String.valueOf(list.get(i)));
        }
        total[0] = list.get(i);
        view.printMessage("---- Total ");
        view.printMessage("Total clientes distintos:    " + total[0]);
        view.printMessage("Total vendas:                " + total[1]);

    }

    /**
     * Função que trata do controller da query 3
     */
    private void query3Controller() throws IOException {
        view.printMessage("Insira o cliente: ");
        String client = in.readLine();
        long startTime = System.nanoTime();
        double[][] result = gv.getClientShoppingLog(client);
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        ITable table = new Table();
        table.table3View(result, client);
    }

    /**
     * Função que trata do controller da query 4
     */
    private void query4Controller() {
        Scanner sc = new Scanner(System.in);
        view.printMessage("Insira o produto: ");
        String product = sc.nextLine();
        long startTime = System.nanoTime();
        double[][] result = gv.query4(product);
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        ITable table = new Table();
        table.table4View(result, product);
    }

    private void query5Controller() throws IOException {
        int n_page = 0;
        view.printMessage("Insira o Cliente: ");
        String client = in.readLine();
        long startTime = System.nanoTime();
        String[][] result = gv.getClientsFavoriteProducts(client);
        List<String> list = new ArrayList<>();
        for(String[] c : result) {
            list.add("Produto: " + c[0] + " | Quantidade: " + c[1]);
        }
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        String choice = "-1";
        while(!choice.equals("0")) {
            view.printMessage("=================================");
            view.printMessage("### Produtos que mais comprou ###");
            view.printMessage("###       Cliente " + client + "       ###");
            view.printMessage("=================================");
            pages = new Pages(list.size(),list);
            pages.show(n_page);
            pages.choices();
            choice = null;
            choice = in.readLine();
            view.printMessage("teste");
            if (choice.equals("n")) {
                view.printMessage(choice);
                n_page++;
            }
            else if(choice.equals("p")) {
                view.printMessage(choice);
                n_page--;
            }
            else if(choice.equals("c")) {
                view.printMessage(choice);
                view.printMessage("Número da página: ");
                n_page = Integer.parseInt((in.readLine()));
            } else
                choice = "0";
        }
    }

    /**
     * Função que trata do controller da query 7
     */
    void query7Controller() {
        long startTime = System.nanoTime();
        String[][][] result = gv.query7();
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        System.out.println("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        view.query7View(result);
    }

    /**
     * Função que trata do controller da query 6
     */
    private void query6Controller() throws IOException {
        int n_page = 0;
        view.printMessage("Insira o número de produtos que deseja ver: ");
        int n = Integer.parseInt(in.readLine());
        long startTime = System.nanoTime();
        String[][] result = gv.query6(n);
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        for(int i = 0; i < n; i++) {
            System.out.println("---- Produto " + result[i][0] + "\n" + "Quantidade: " + result[i][1] + "\n" + "Clientes distintos: " + result[i][2]);
        }
    }

    /**
     * Função que trata do controller da query 8
     */
    private void query8Controller() throws IOException {
        int n_page = 0;
        long startTime = System.nanoTime();
        view.printMessage("Quantos pretende ver?");
        int n = Integer.parseInt(in.readLine());
        String[][] result = gv.query8(n);
        List<String> list = new ArrayList<>();
        for(String[] c : result) {
            list.add("Client: " + c[0] + " | Produtos: " + c[1]);
        }
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        String choice = "-1";
        while(!choice.equals("0")) {
            view.printMessage("================================");
            view.printMessage("###       Top Clientes       ###");
            view.printMessage("###      PRODUTOS ÚNICOS     ###");
            view.printMessage("================================");
            pages = new Pages(list.size(),list);
            pages.show(n_page);
            pages.choices();
            choice = null;
            choice = in.readLine();
            view.printMessage("teste");
            if (choice.equals("n")) {
                view.printMessage(choice);
                n_page++;
            }
            else if(choice.equals("p")) {
                view.printMessage(choice);
                n_page--;
            }
            else if(choice.equals("c")) {
                view.printMessage(choice);
                view.printMessage("Número da página: ");
                n_page = Integer.parseInt((in.readLine()));
            } else
                choice = "0";
        }
    }

    /**
     * Função que trata do controller da query 9
     */
    private void query9Controller() throws IOException {
        int n_page = 0;
        long startTime = System.nanoTime();
        view.printMessage("Insira o produto: ");
        String product = in.readLine();
        view.printMessage("Quantos pretende ver?");
        int n = Integer.parseInt(in.readLine());
        String[][] result = gv.query9(product,n);
        List<String> list = new ArrayList<>();
        for(String[] c : result) {
            list.add("Cliente: " + c[0] + " | Gasto: " + c[1]);
        }
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        String choice = "-1";
        while(!choice.equals("0")) {
            view.printMessage("=================================");
            view.printMessage("###       Top Clientes        ###");
            view.printMessage("###      Produto " + product + "       ###");
            view.printMessage("=================================");
            pages = new Pages(list.size(),list);
            pages.show(n_page);
            pages.choices();
            choice = null;
            choice = in.readLine();
            view.printMessage("teste");
            if (choice.equals("n")) {
                view.printMessage(choice);
                n_page++;
            }
            else if(choice.equals("p")) {
                view.printMessage(choice);
                n_page--;
            }
            else if(choice.equals("c")) {
                view.printMessage(choice);
                view.printMessage("Número da página: ");
                n_page = Integer.parseInt((in.readLine()));
            } else
                choice = "0";
        }
    }

    /* void menu(SGV sgv) */
    void menu() throws IOException {

        int querie = -1;
        view.cleanConsole();
        while (querie != 0)
        {
            view.printMenu();
            try {
                querie = Integer.parseInt(in.readLine());
            } catch (InputMismatchException e) {
                view.printMessage("Terminando a aplicação...");
                querie = 0;
            }

            switch (querie)
            {
                case 1:
                    query1Controller();
                    break;
                case 2:
                    query2Controller();
                    break;
                case 3:
		            query3Controller();
                    /*controllerQuery3(sgv);*/
                    break;
                case 4:
                    query4Controller();
                    /*controllerQuery4(sgv);*/
                    break;
                case 5:
                    query5Controller();
                    break;
                case 6:
                    query6Controller();
                    /*controllerQuery6(sgv);*/
                    break;
                case 7:
                    query7Controller();
                    break;
                case 8:
                    query8Controller();
                    /*controllerQuery8(sgv);*/
                    break;
                case 9:
                    query9Controller();
                    /*controllerQuery9(sgv);*/
                    break;
                case 10:
                    /*controllerQuery10(sgv);*/
                    break;
                case 11:
                    /*controllerQuery11(sgv);*/
                    break;
                case 12:
                    /*controllerQuery12(sgv);*/
                    break;
                default:
                    querie = 0;
                    break;
            }
        }
    }
}
