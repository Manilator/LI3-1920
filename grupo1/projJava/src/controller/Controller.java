package controller;

import model.SGV;
import view.View;

import java.io.IOException;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

public class Controller {
    public View view;
    private final SGV sgv;
    private final Scanner in;

    public Controller() {
        this.view = new View();
        this.sgv = new SGV();
        in = new Scanner(System.in);
    }

    public void startController() throws IOException {
        System.out.println("Starting Controller!\n----------");
        menu();
        System.out.println("Closing Controller!\n----------");
    }

    /* void menu(SGV sgv) */
    void menu() throws IOException {
        String choice;
        int querie = -1;
        int initial = 0;
        /*StartValues sv = initStartValues();
        cleanConsole();*/
        while (querie != 0)
        {
            view.printMenu();
            querie = in.nextInt();
            while (querie != 1 && initial != 1 && querie != 0 && querie <= 13)
            {
                view.printMessage("Faça a querie 1 primeiro para carregamento dos dados.\n");
                querie = in.nextInt();
            }
            switch (querie)
            {
                case 1:
                    if(initial == 1) {
                        view.printMessage("A libertar dados antigos...\n");
                        /*destroyStartValues(sv);
                        destroySGV(sgv);
                        sgv = initSGV();
                        sv = initStartValues();*/

                    }
                    /*controllerQuery1(sv, sgv);*/
                    initial = 1;
                    break;
                case 2:
                    long startTime = System.nanoTime();
                    sgv.startSGV();
                    long stopTime = System.nanoTime();
                    double time = (double) (stopTime - startTime) / 1_000_000_000;
                    System.out.println("Tempo a ler os dados: " + time + " segundos");
                    view.printMessage(String.valueOf("Clientes válidos lidos: " + this.sgv.getClientsSize()));
                    view.printMessage(String.valueOf("Produtos válidos lidos: " + this.sgv.getProductsSize()));
                    view.printMessage(String.valueOf("Produtos lidos: " + this.sgv.getReadProducts()));
                    view.printMessage(String.valueOf("Vendas válidos lidas: " + this.sgv.getValidSales()));
                    view.printMessage(String.valueOf("Vendas lidas: " + this.sgv.getReadSales()));
                    /*controllerQuery2(sgv);*/
                    break;
                case 3:
                    System.out.println("Query 3");
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
                case 13:
                    /*controllerQuery13(sv);*/
                    break;
                default:
                    querie = 0;
                    break;
            }
        }
    }
}
