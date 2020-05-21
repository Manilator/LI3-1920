package controller;

import model.GestVendasModel;
import model.IGestVendasModel;
import view.GestVendasView;
import view.IGestVendasView;
import view.IPages;
import view.Pages;

import java.io.IOException;
import java.util.*;

import static Utils.Constants.N_BRANCHES;
import static Utils.Constants.N_MONTHS;

public class GestVendasController implements IGestVendasController {
    public IGestVendasView view;
    private final IGestVendasModel gv;
    private final Scanner in;
    private IPages pages;

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
        in = new Scanner(System.in);
    }

    public void startController() throws IOException {
        menu();
    }

    private void query1Controller() {
        int n_page = 0;
        long startTime = System.nanoTime();
        List<String> list = gv.getProductNeverBought();
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        String choice = "-1";
        Scanner sc = new Scanner(System.in);
        while(!choice.equals("0")) {
            view.printMessage("==================================");
            view.printMessage("#### Produtos nunca comprados ####");
            view.printMessage("==================================");
            pages = new Pages(list.size(),list);
            pages.show(n_page);
            pages.choices();
            choice = sc.nextLine();
            switch (choice) {
                case "n":
                    n_page++;
                case "p":
                    n_page--;
                case "c":
                    view.printMessage("Número da página: ");
                    n_page = in.nextInt();
                default:
                    choice = "0";
            }
        }
    }

    private void query2Controller() {
        int month = 0;
        view.printMessage("Insira o mês:");
        while(month < 1 || month > 12) {
            month = in.nextInt();
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
  
    private void query3Controller() {
        Scanner sc = new Scanner(System.in);
        String client = sc.nextLine();
        long startTime = System.nanoTime();
        double[][] result = gv.getClientShoppingLog(client);
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        view.query3View(result);
    }
  
    private void query4Controller() {
        Scanner sc = new Scanner(System.in);
        view.printMessage("Insira o produto: ");
        String product = sc.nextLine();
        long startTime = System.nanoTime();
        double[][] result = gv.query4(product);
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        view.query4View(result);
    }

    private void query6Controller() {
        // Resolver os scanners
        Scanner sr = new Scanner(System.in);
        int n_page = 0;
        view.printMessage("Insira o número de produtos que deseja ver: ");
        int n = sr.nextInt();
        String[][] result = gv.query6(n);
        List<String> list = new ArrayList<>();
        for(int i = 0; i < N_MONTHS; i++) {
            list.add("---- Produto " + result[i][0] + "\n" + "Quantidade: " + result[i][1] + "\n" + "Clientes distintos: " + result[i][2]);
        }
        String choice = "-1";
        Scanner sc = new Scanner(System.in);
        while(!choice.equals("0")) {
            Pages pages = new Pages(list.size(),list);
            pages.show(n_page);
            pages.choices();
            choice = sc.nextLine();
            switch (choice) {
                case "n":
                    n_page++;
                case "p":
                    n_page--;
                case "c":
                    view.printMessage("Número da página: ");
                    n_page = sr.nextInt();
                default:
                    choice = "0";
            }
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
                querie = in.nextInt();
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
                    /*controllerQuery5(sgv);*/
                    break;
                case 6:
                    query6Controller();
                    /*controllerQuery6(sgv);*/
                    break;
                case 7:
                    /*controllerQuery7(sgv);*/
                    break;
                case 8:
                    /*controllerQuery8(sgv);*/
                    break;
                case 9:
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
