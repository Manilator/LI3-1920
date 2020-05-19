package controller;

import model.GestVendasModel;
import model.IGestVendasModel;
import view.GestVendasView;
import view.IGestVendasView;
import view.IPages;
import view.Pages;

import java.io.IOException;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

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
        System.out.println("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
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

    void query1Controller() {
        int n_page = 0;
        List<String> list = gv.query1();
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
                case "n" -> n_page++;
                case "p" -> n_page--;
                case "c" -> {
                    view.printMessage("Número da página: ");
                    n_page = in.nextInt();
                }
                default -> choice = "0";
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
                    /*controllerQuery2(sgv);*/
                    break;
                case 3:

                    /*controllerQuery3(sgv);*/
                    break;
                case 4:
                    /*controllerQuery4(sgv);*/
                    break;
                case 5:
                    /*controllerQuery5(sgv);*/
                    break;
                case 6:
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
