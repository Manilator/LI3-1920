package controller;

import Utils.Crono;
import model.GestVendasModel;
import model.IGestVendasModel;
import view.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;

import static Utils.Constants.N_BRANCHES;

public class GestVendasController implements IGestVendasController {
    public IGestVendasView view;
    private IGestVendasModel gv;
    private final BufferedReader in;
    private IPages pages;
    private Crono crono;


    /**
     * Construtor vazio do controller
     */
    public GestVendasController() {
        this.crono = new Crono();
        this.view = new GestVendasView();
        crono.start();
        this.gv = new GestVendasModel("data/Clientes.txt", "data/Produtos.txt", "data/Vendas_1M.txt");
        view.printMessage(crono.getTImeString());
        view.printMessage(String.valueOf("Clientes válidos: " + this.gv.getClientsSize()));
        view.printMessage(String.valueOf("Clientes lidos: " + this.gv.getReadClients()));
        view.printMessage(String.valueOf("Produtos válidos: " + this.gv.getProductsSize()));
        view.printMessage(String.valueOf("Produtos lidos: " + this.gv.getReadProducts()));
        view.printMessage(String.valueOf("Vendas válidos: " + this.gv.getValidSales()));
        view.printMessage(String.valueOf("Vendas lidas: " + this.gv.getReadSales()));
        in = new BufferedReader(new InputStreamReader(System.in));
    }

    /**
     * Construtor custom do controller
     */
    public GestVendasController(String clientPath, String productPath, String salesPath) {
        this.view = new GestVendasView();
        long startTime = System.nanoTime();
        this.gv = new GestVendasModel(clientPath, productPath, salesPath);
        long stopTime = System.nanoTime();
        double time = (double) (stopTime - startTime) / 1_000_000_000;
        view.printMessage("Tempo a ler os dados: " + String.format("%.3f", time) + " segundos");
        readStats();
        in = new BufferedReader(new InputStreamReader(System.in));
    }

    private void readStats() {
        view.printMessage(String.valueOf("Clientes válidos: " + this.gv.getClientsSize()));
        view.printMessage(String.valueOf("Clientes lidos: " + this.gv.getReadClients()));
        view.printMessage(String.valueOf("Produtos válidos: " + this.gv.getProductsSize()));
        view.printMessage(String.valueOf("Produtos lidos: " + this.gv.getReadProducts()));
        view.printMessage(String.valueOf("Vendas válidos: " + this.gv.getValidSales()));
        view.printMessage(String.valueOf("Vendas lidas: " + this.gv.getReadSales()));
    }

    /**
     * Função que inicia o controller
     * @throws IOException Exceção se ocorrer erros ao ler os ficheiros
     */
    public void startController() throws IOException, ClassNotFoundException {
        menu();
    }

    private String askProduct() throws IOException {
        view.printMessage("Insira o produto: ");
        return in.readLine();
    }

    private String askClient() throws IOException {
        view.printMessage("Insira o Cliente: ");
        return in.readLine();
    }

    private int askMonth() throws IOException {
        int month = 0;
        int i = 0;
        view.printMessage("Insira o mês: ");
        while(month < 1 || month > 12) {
            if (i != 0) view.printMessage("Mês inválido.");
            month = Integer.parseInt(in.readLine());
            i++;
        }
        return month;
    }

    private int askN() throws IOException {
        int n = 0;
        int i = 0;
        view.printMessage("Insira quantos pretende ver: ");
        while(n <= 0) {
            if (i != 0) view.printMessage("Número inválido.");
            n = Integer.parseInt(in.readLine());
            i++;
        }
        return n;
    }

    /**
     * Função que trata do controller da query 1
     */
    private void query1Controller() throws IOException {
        try {
            int n_page = 0;
            view.cleanConsole();
            crono.start();
            List<String> list = gv.getProductNeverBought();
            view.printMessage(crono.getTImeString());
            String choice = "-1";
            if (list.size() == 0) {
                view.printMessage("Não existe nenhum produto.");
            } else {
                while(!choice.equals("0")) {
                    view.printMessage("==================================");
                    view.printMessage("#### Produtos nunca comprados ####");
                    view.printMessage("==================================");
                    pages = new Pages(list.size(),10,list);
                    pages.show(n_page);
                    pages.choices();
                    choice = null;
                    choice = in.readLine();
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
        } catch (Exception e) {
            view.printMessage("Não existe nenhum produto.");
        }

    }

    /**
     * Função que trata do controller da query 2
     */
    private void query2Controller() throws IOException {
        int month = askMonth();

        crono.start();
        List<Integer> list = gv.query2(month);
        view.printMessage(crono.getTImeString());

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
        try {
            String client = askClient();
            crono.start();
            double[][] result = gv.getClientShoppingLog(client);
            view.printMessage(crono.getTImeString());

            ITable table = new Table();
            table.table3View(result, client);
        } catch (Exception e) {
            view.printMessage("Cliente inválido.");
        }
    }

    /**
     * Função que trata do controller da query 4
     */
    private void query4Controller() throws IOException {
        try {
            String product = askProduct();

            crono.start();
            double[][] result = gv.query4(product);
            view.printMessage(crono.getTImeString());

            ITable table = new Table();
            table.table4View(result, product);
        } catch (Exception e) {
            view.printMessage("Produto inválido.");
        }

    }

    private void query5Controller() throws IOException {
        try {
            int n_page = 0;
            String client = askClient();

            crono.start();
            String[][] result = gv.getClientsFavoriteProducts(client);
            view.printMessage(crono.getTImeString());

            List<String> list = new ArrayList<>();
            for(String[] c : result) {
                list.add("Produto: " + c[0] + " | Quantidade: " + c[1]);
            }

            String choice = "-1";
            while(!choice.equals("0")) {
                view.printMessage("=================================");
                view.printMessage("### Produtos que mais comprou ###");
                view.printMessage("###       Cliente " + client + "       ###");
                view.printMessage("=================================");
                pages = new Pages(list.size(),10,list);
                pages.show(n_page);
                pages.choices();
                choice = null;
                choice = in.readLine();
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
        } catch (Exception e) {
            view.printMessage("Cliente inválido.");
        }
    }

    /**
     * Função que trata do controller da query 6
     */
    private void query6Controller() throws IOException {
        int n_page = 0;
        int n = askN();

        crono.start();
        String[][] result = gv.query6(n);
        view.printMessage(crono.getTImeString());

        List<String> list = new ArrayList<>();
        for(int i = 0; i < n; i++) {
            list.add("---- Produto " + result[i][0] + "\n" + "Quantidade: " + result[i][1] + "\n" + "Clientes distintos: " + result[i][2]);
        }

        String choice = "-1";
        while(!choice.equals("0")) {
            view.printMessage("================================");
            view.printMessage("###       Top Produtos       ###");
            view.printMessage("================================");
            pages = new Pages(list.size(),3,list);
            pages.show(n_page);
            pages.choices();
            choice = null;
            choice = in.readLine();
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
        crono.start();
        String[][][] result = gv.query7();
        view.printMessage(crono.getTImeString());

        view.query7View(result);
    }

    /**
     * Função que trata do controller da query 8
     */
    private void query8Controller() throws IOException {
        int n_page = 0;
        int n = askN();

        crono.start();
        String[][] result = gv.query8(n);
        view.printMessage(crono.getTImeString());

        List<String> list = new ArrayList<>();
        for(String[] c : result) {
            list.add("Client: " + c[0] + " | Produtos: " + c[1]);
        }

        String choice = "-1";
        while(!choice.equals("0")) {
            view.printMessage("================================");
            view.printMessage("###       Top Clientes       ###");
            view.printMessage("###      PRODUTOS ÚNICOS     ###");
            view.printMessage("================================");
            pages = new Pages(list.size(),10,list);
            pages.show(n_page);
            pages.choices();
            choice = null;
            choice = in.readLine();
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
        try {
            int n_page = 0;
            String product = askProduct();
            int n = askN();

            crono.start();
            String[][] result = gv.query9(product,n);
            view.printMessage(crono.getTImeString());

            List<String> list = new ArrayList<>();
            for(String[] c : result) {
                list.add("Cliente: " + c[0] + " | Gasto: " + c[1]);
            }

            String choice = "-1";
            while(!choice.equals("0")) {
                view.printMessage("=================================");
                view.printMessage("###       Top Clientes        ###");
                view.printMessage("###      Produto " + product + "       ###");
                view.printMessage("=================================");
                pages = new Pages(list.size(),10,list);
                pages.show(n_page);
                pages.choices();
                choice = null;
                choice = in.readLine();
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
        } catch (Exception e) {
            view.printMessage("Produto inválido.");
        }
    }

    /**
     * Função que trata do controller da query 10
     */
    void query10Controller() {
        crono.start();
        Map<String, double[][]> result =  gv.query10();
        view.printMessage(crono.getTImeString());;

        view.query10View(result);
    }

    /**
     * Função que trata do controller da query estatistica 2
     */
    void queryE2(){
        gv.getNumberOfDistinctClients();/*int[][]*/
        gv.getShoppingFrequency();/*int[]*/
        gv.getBillingByMonthAndBranch(); /*double[][]*/
    }

    void loadController() throws IOException, ClassNotFoundException {
        view.printLoad();
        int choice = Integer.parseInt(in.readLine());
        if (choice == 1) {
            view.loadChoice();
            choice = Integer.parseInt(in.readLine());
            view.printMessage("Insira o path: ");
            String path = in.readLine();
            if (choice == 1) {
                view.printMessage("A ler clientes... ");
                this.gv.parseClients(path);
            } else if (choice == 2) {
                view.printMessage("A ler produtos... ");
                this.gv.parseProducts(path);
            } else if (choice == 3) {
                view.printMessage("A ler vendas... ");
                this.gv.parseSales(path);
            } else {
                view.printMessage("A voltar para o menu...");
            }
        } else if (choice == 2){
            view.printMessage("Insira o path: ");
            String path = in.readLine();
            this.gv = GestVendasModel.load(path);
        } else if (choice == 3) {
            view.printMessage("A limpar dados... ");
            view.printMessage("Insira o path dos clientes: ");
            String clients = in.readLine();
            view.printMessage("Insira o path dos produtos: ");
            String products = in.readLine();
            view.printMessage("Insira o path das vendas: ");
            String sales = in.readLine();
            view.printMessage("A ler dados... ");
            crono.start();
            this.gv = new GestVendasModel(clients, products, sales);
            view.printMessage(crono.getTImeString());
            readStats();
        } else {
            view.printMessage("A voltar para o menu...");
        }

    }

    void saveController() throws IOException {
        view.printMessage("Insira o path: ");
        String path = in.readLine();
        gv.save(path);
    }

    void menu() throws IOException, ClassNotFoundException {

        int querie = -1;
        view.cleanConsole();
        while (querie != 0)
        {
            view.printMenu();
            try {
                querie = Integer.parseInt(in.readLine());
            } catch (Exception e) {
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
                    break;
                case 4:
                    query4Controller();
                    break;
                case 5:
                    query5Controller();
                    break;
                case 6:
                    query6Controller();
                    break;
                case 7:
                    query7Controller();
                    break;
                case 8:
                    query8Controller();
                    break;
                case 9:
                    query9Controller();
                    break;
                case 10:
                    query10Controller();
                    break;
                case 11:
                    /*controllerQuery11(sgv);*/
                    break;
                case 12:
                    queryE2();
                    break;
                case 13:
                    loadController();
                    break;
                case 14:
                    saveController();
                    break;
                default:
                    querie = 0;
                    view.printMessage("Terminando a aplicação...");
                    break;
            }
        }
    }
}
