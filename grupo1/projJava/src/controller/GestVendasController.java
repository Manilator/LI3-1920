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

import static Utils.Constants.*;

public class GestVendasController implements IGestVendasController {
    private final BufferedReader in;
    private IGestVendasView view;
    private IGestVendasModel gv;
    private IPages pages;

    /**
     * Construtor vazio do controller
     */
    public GestVendasController() {
        this.view = new GestVendasView();
        Crono.start();
        this.gv = new GestVendasModel(DefaultClientsPath, DefaultProductsPath, DefaultSalesPath);
        view.printMessage(Crono.getTimeString());
        view.printMessage("Clientes válidos: " + this.gv.getClientsSize());
        view.printMessage("Clientes lidos: " + this.gv.getReadClients());
        view.printMessage("Produtos válidos: " + this.gv.getProductsSize());
        view.printMessage("Produtos lidos: " + this.gv.getReadProducts());
        view.printMessage("Vendas válidos: " + this.gv.getValidSales());
        view.printMessage("Vendas lidas: " + this.gv.getReadSales());
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

    /**
     * Função que pede um codigo de produto
     * @return String codigo de produto
     */
    private String askProduct() throws IOException {
        view.printMessage("Insira o produto: ");
        return in.readLine();
    }

    /**
     * Função que pede um codigo de cliente
     * @return Devolve uma string do codigo do cliente
     */
    private String askClient() throws IOException {
        view.printMessage("Insira o Cliente: ");
        return in.readLine();
    }

    /**
     * Função que pede um certo mes
     * @return Devole um int do mes pedido
     */
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

    /**
     * Função que pede uma quantidade para ser inserida
     * @return Devolve um int da quantidade inserida
     */
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
    private void query1Controller() {
        try {
            int n_page = 0;
            view.cleanConsole();
            Crono.start();
            List<String> list = gv.getProductNeverBought();
            view.printMessage(Crono.getTimeString());
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
    private void query2Controller() {
        try{
            int month = askMonth();

            Crono.start();
            List<Integer> list = gv.query2(month);
            view.printMessage(Crono.getTimeString());

            int[] total = new int[2];
            Arrays.fill(total,0);
            int i = 0;
            for (int j = 1; i < N_BRANCHES*2; i++, j++) {
                view.printMessage("---- Filial " + j);
                view.printMessage("Número distinto de clientes: " + list.get(i++));
                total[1] += list.get(i);
                view.printMessage("Número de vendas:            " + list.get(i));
            }
            total[0] = list.get(i);
            view.printMessage("---- Total ");
            view.printMessage("Total clientes distintos:    " + total[0]);
            view.printMessage("Total vendas:                " + total[1]);

        } catch (Exception e) {
            view.printMessage("Mês inválido.");
        }
    }

    /**
     * Função que trata do controller da query 3
     */
    private void query3Controller() {
        try {
            String client = askClient();
            Crono.start();
            double[][] result = gv.getClientShoppingLog(client);
            view.printMessage(Crono.getTimeString());

            ITable table = new Table();
            table.table3View(result, client);
        } catch (Exception e) {
            view.printMessage("Cliente inválido.");
        }
    }

    /**
     * Função que trata do controller da query 4
     */
    private void query4Controller() {
        try {
            String product = askProduct();

            Crono.start();
            double[][] result = gv.query4(product);
            view.printMessage(Crono.getTimeString());

            ITable table = new Table();
            table.table4View(result, product);
        } catch (Exception e) {
            view.printMessage("Produto inválido.");
        }

    }

    /**
     * Função que trata do controller da query 5
     */
    private void query5Controller() {
        try {
            int n_page = 0;
            String client = askClient();

            Crono.start();
            String[][] result = gv.getClientsFavoriteProducts(client);
            view.printMessage(Crono.getTimeString());

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
    private void query6Controller() {
        try {
            int n_page = 0;
            int n = askN();

            Crono.start();
            String[][] result = gv.query6(n);
            view.printMessage(Crono.getTimeString());

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
            view.printMessage("Mês inválido.");
        }
    }

    /**
     * Função que trata do controller da query 7
     */
    void query7Controller() {
        try {
            Crono.start();
            String[][][] result = gv.query7();
            view.printMessage(Crono.getTimeString());

            view.query7View(result);
        } catch (Exception e){
            view.printMessage("Erro ao executar, tente novamente.");
        }

    }

    /**
     * Função que trata do controller da query 8
     */
    private void query8Controller() {
        try {
            int n_page = 0;
            int n = askN();

            Crono.start();
            String[][] result = gv.query8(n);
            view.printMessage(Crono.getTimeString());

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
        } catch (Exception e){
            view.printMessage("Quantidade inválida.");
        }

    }

    /**
     * Função que trata do controller da query 9
     */
    private void query9Controller() {
        try {
            int n_page = 0;
            String product = askProduct();
            int n = askN();

            Crono.start();
            String[][] result = gv.query9(product,n);
            view.printMessage(Crono.getTimeString());

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
        try{
            Crono.start();
            Map<String, double[][]> result =  gv.query10();
            view.printMessage(Crono.getTimeString());

            view.query10View(result);
        } catch (Exception e){
            view.printMessage("Erro ao executar, tente novamente.");
        }
    }

    /**
     * Função que trata do controller da query estatistica 1
     */
    void queryE1(){
        gv.statisticalConsult();
    }

    /**
     * Função que trata do controller da query estatistica 2
     */
    void queryE2(){
        gv.getNumberOfDistinctClients();/*int[][]*/
        gv.getShoppingFrequency();/*int[]*/
        gv.getBillingByMonthAndBranch(); /*double[][]*/
    }

    void loadController() {
        try {
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
                Crono.start();
                this.gv = new GestVendasModel(clients, products, sales);
                view.printMessage(Crono.getTimeString());
                readStats();
            } else {
                view.printMessage("A voltar para o menu...");
            }
        } catch (IOException e){
            view.printMessage("Ficheiro não encontrado.");
        } catch (ClassNotFoundException e){
            view.printMessage("Insira os dados corretamente.");
        }


    }

    void saveController() {
        try {
            view.printMessage("Insira o path: ");
            String path = in.readLine();
            gv.save(path);
        } catch (IOException e){
            view.printMessage("Local para guardar inválido.");
        }

    }

    void menu() {

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
                    queryE1();
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
