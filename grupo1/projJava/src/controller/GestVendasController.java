package controller;

import Utils.Crono;
import exceptions.InvalidClient;
import exceptions.InvalidMonth;
import exceptions.InvalidNumber;
import exceptions.InvalidProduct;
import model.Client;
import model.GestVendasModel;
import model.IGestVendasModel;
import model.Product;
import view.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import static Utils.Constants.*;

/**
 * Classe que controla o fluxo do programa
 */
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

    /**
     * Numero de valores lidos total e validos
     */
    private void readStats() {
        view.printMessage("Clientes válidos: " + this.gv.getClientsSize());
        view.printMessage("Clientes lidos: " + this.gv.getReadClients());
        view.printMessage("Produtos válidos: " + this.gv.getProductsSize());
        view.printMessage("Produtos lidos: " + this.gv.getReadProducts());
        view.printMessage("Vendas válidos: " + this.gv.getValidSales());
        view.printMessage("Vendas lidas: " + this.gv.getReadSales());
    }

    /**
     * Função que inicia o controller
     * @throws IOException Exceção se ocorrer erros ao ler os ficheiros
     */
    public void startController() { menu(); }

    /**
     * Função que pede um codigo de produto
     * @return String codigo de produto
     */
    private String askProduct() throws InvalidProduct{
        String produto = null;
        view.printMessage("Insira o produto: ");
        try {
            produto = in.readLine();
            Product test = new Product(produto);
            if(!test.validate()) throw new InvalidProduct();
        } catch (IOException e) {
            view.printMessage("Produto inválido. ");
        }
        return produto;
    }

    /**
     * Função que pede um codigo de cliente
     * @return Devolve uma string do codigo do cliente
     */
    private String askClient() throws InvalidClient {
        String cliente = null;
        view.printMessage("Insira o Cliente: ");
        try {
            cliente = in.readLine();
            Client test = new Client(cliente);
            if(!test.validate()) throw new InvalidClient();
        } catch (IOException e) {
            view.printMessage("Cliente inválido. ");
        }
        return cliente;
    }

    /**
     * Função que pede um certo mes
     * @return Devole um int do mes pedido
     */
    private int askMonth() throws InvalidMonth {
        int month = 0;
        view.printMessage("Insira o mês: ");
        try {
            month = Integer.parseInt(in.readLine());
            if (month < 1 || month > 12) {
                throw new InvalidMonth();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return month;
    }

    /**
     * Função que pede uma quantidade para ser inserida
     * @return Devolve um int da quantidade inserida
     */
    private int askN() throws InvalidNumber {
        int n = 0;
        view.printMessage("Insira quantos pretende ver: ");
        try {
            n = Integer.parseInt(in.readLine());
            if (n <= 0) {
                throw new InvalidNumber();
            }
        } catch (IOException e) {
            e.printStackTrace();
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
                    pages = new Pages(list.size(),ELEMENTS_PER_PAGE,list);
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
            List<Integer> list = gv.totalSalesCountAndDistinctBuyers(month);
            view.printMessage(Crono.getTimeString());
            view.query2View(list);
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
            double[][] result = gv.productInfoByMonth(product);
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
                pages = new Pages(list.size(),ELEMENTS_PER_PAGE,list);
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
            String[][] result = gv.topMostBoughtProducts(n);
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
            view.printMessage("Quantidade inválida.");
        }
    }

    /**
     * Função que trata do controller da query 7
     */
    void query7Controller() {
        try {
            Crono.start();
            String[][][] result = gv.top3BuyersByBranch();
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
            String[][] result = gv.topClientsWhoBoughtDistinctProducts(n);
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
                pages = new Pages(list.size(),ELEMENTS_PER_PAGE,list);
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
            String[][] result = gv.topNBuyersAndMoneySpent(product,n);
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
                pages = new Pages(list.size(),ELEMENTS_PER_PAGE,list);
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
        } catch (InvalidNumber e) {
            view.printMessage("Quantidade inválida.");
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
            Map<String, double[][]> result =  gv.totalBillingByMonthAndBranch();
            view.printMessage(Crono.getTimeString());
            String product = askProduct();
            ITable table = new Table();
            while (true) {
                view.printMessage("---- Produto " + product);
                table.tableE2View(result.get(product));
                view.printMessage("(Caso pretenda voltar ao menu, insira qualquer carater)");
                product = askProduct();
            }
        } catch (Exception e){
            view.printMessage("Produto inválido.");
        }
    }

    /**
     * Função que trata do controller da query estatistica 1
     */
    void queryE1(){
        Crono.start();
        String[] list = gv.statisticalConsult();
        view.printMessage(Crono.getTimeString());
        view.queryE1View(list);
    }

    /**
     * Função que trata do controller da query estatistica 2
     */
    void queryE2(){
        Crono.start();
        int[][] result = gv.getNumberOfDistinctClients();
        int[][] result2 = new int[1][];
        result2[0] = gv.getShoppingFrequency();
        double[][] result3 = gv.getBillingByMonthAndBranch();
        view.printMessage(Crono.getTimeString());
        ITable table = new Table();
        view.printMessage("\n---- Número de distintos clientes que compraram por mês filial a filial: ");
        table.tableE2View(result);
        view.printMessage("\n---- Número total de compras por mês: ");
        table.tableE2View(result2);
        view.printMessage("\n---- Faturação total por mês filial a filial: ");
        table.tableE2View(result3);
    }

    /**
     * Funçao responsavel pelo carregamento de dados
     */
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

    /**
     * Funçao responsavel pelo armazenamento de dados
     */
    void saveController() {
        try {
            view.printMessage("Insira o path: ");
            String path = in.readLine();
            gv.save(path);
        } catch (IOException e){
            view.printMessage("Local para guardar inválido.");
        }
    }

    /**
     * Funçao principal encarregue pelo controlo do menu
     */
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

            switch (querie) {
                case 1 -> query1Controller();
                case 2 -> query2Controller();
                case 3 -> query3Controller();
                case 4 -> query4Controller();
                case 5 -> query5Controller();
                case 6 -> query6Controller();
                case 7 -> query7Controller();
                case 8 -> query8Controller();
                case 9 -> query9Controller();
                case 10 -> query10Controller();
                case 11 -> queryE1();
                case 12 -> queryE2();
                case 13 -> loadController();
                case 14 -> saveController();
                default -> {
                    querie = 0;
                    view.printMessage("Terminando a aplicação...");
                }
            }
        }
    }
}
