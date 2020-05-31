package model;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.BufferedReader;
import java.io.Serializable;
import java.io.FileReader;
import java.io.IOException;
import java.io.File;

import java.util.stream.Collectors;
import java.util.Comparator;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.Set;

import static Utils.Constants.N_BRANCHES;
import static Utils.Constants.N_MONTHS;

public class GestVendasModel implements IGestVendasModel, Serializable {

    private static final long serialVersionUID = -633886111828325882L;
    private final IClientCatalog client_catalog; /**< Cátalogo de clientes */
    private final IProductCatalog product_catalog; /**< Cátalogo de produto */
    private final IBillingCatalog billing_catalog; /**< Cátalogo de faturação */
    private final IBranchCatalog branches_catalog; /**< Cátalogo de filiais */
    private final String saleFileName;
    private int readClients;
    private int readProducts;
    private int readSales;
    private int validSales;

    /**
     * Construtor com paths do model
     */
    public GestVendasModel(String clientsPath, String productPath, String salesPath){
        this.client_catalog = new ClientCatalog();
        this.product_catalog = new ProductCatalog();
        this.billing_catalog = new BillingCatalog();
        this.branches_catalog = new BranchCatalog();
        this.readClients = 0;
        this.readProducts = 0;
        this.readSales = 0;
        this.saleFileName = salesPath;
        parseClients(clientsPath);
        parseProducts(productPath);
        parseSales(salesPath);
    }

    public void parseClients(String clientPath) {
        File file = new File(clientPath);

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String clientCode;

            while ((clientCode = reader.readLine()) != null) {
                this.client_catalog.insertClient(clientCode);
                this.readClients++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void parseProducts(String productPath) {
        File file = new File(productPath);

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String productCode;

            while ((productCode = reader.readLine()) != null) {
                if (this.product_catalog.insertProduct(productCode)) {
                    this.billing_catalog.addBillingProduct(productCode);
                }
                this.readProducts++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void parseSales(String salesPath) {
        File file = new File(salesPath);

        List<String> lista_vendas = new ArrayList<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String sale_line;
            while ((sale_line = reader.readLine()) != null) {
                lista_vendas.add(sale_line);
            }
            //lista_vendas = Files.readAllLines(Paths.get(salesPath), StandardCharsets.UTF_8);
            this.readSales = lista_vendas.size();
            validSales = 0;
            lista_vendas
                    .parallelStream()
                    .map(Sale::new)
                    .filter(e -> e.validSale() && this.client_catalog.existClient(e.getClient())
                            && this.product_catalog.existProduct(e.getProduct()))
                    .collect(Collectors.toList())
                    .forEach(e -> {this.billing_catalog.updateBillings(e); this.branches_catalog.updateBranches(e); this.validSales++;});

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Lista ordenada alfabeticamente com os códigos dos produtos nunca comprados e o seu respetivo total
     * @return Lista ordenada com os códigos de produtos nunca comprados
     */
    public List<String> getProductNeverBought() {
        Map<String,String> allProductsBought = this.branches_catalog.getProductsBought();
        return this.product_catalog.getProductsNotBought(allProductsBought);
    }

    /**
     * (!!!)
     * @return (!!!)
     */
    public List<Integer> query2(int month) {

        List<Integer> list = new ArrayList<>();
        for(int i = 0; i < N_BRANCHES; i++) {
            list.add(this.branches_catalog
                            .distinctClientsMonth(month, i + 1));
            list.add(this.billing_catalog
                            .getTotalSalesMonth(month, i + 1));
        }
        list.add(this.branches_catalog.distinctClientsMonth(month));
        return list;
    }

    /**
     * Dado um código de cliente, determinar, para cada mês, quantas compras fez, quantos produtos distintos comprou e quanto gastou no total
     * @param clientCode Code of the selected client
     * @return Array de doubles com numero de compras, produtos distintos e valor total gasto, em cada mês
     */
    public double[][] getClientShoppingLog(String clientCode){
        return this.branches_catalog.getClientShoppingLog(clientCode);
    }

    /**
     * (!!!)
     * @return (!!!)
     */
    public double[][] query4(String product) {
        double[][] array = new double[N_MONTHS][3];
        int[] salesMonth = this.billing_catalog.getNSalesProduct(product);
        double[] billedMonth = this.billing_catalog.getTotalBilledMonth(product);
        int[] clientsMonth = this.branches_catalog.getTotalDistinctsClientsProductMonth(product);

        for (int i = 0; i < N_MONTHS; i++) {
            array[i][0] = salesMonth[i];
            array[i][1] = billedMonth[i];
            array[i][2] = clientsMonth[i];
        }
        return array;
    }

    /**
     * Dado um código de cliente retorna uma lista ordenada com os códigos de produtos mais comprados pelo mesmo
     * @param clientCode String com o código do cliente
     * @return Lista de strings com códigos de produtos mais comprados
     */
    public String[][] getClientsFavoriteProducts(String clientCode){
        return this.branches_catalog.getClientsFavoriteProducts(clientCode);
    }

    /**
     * (!!!)
     * @return (!!!)
     */
    public String[][] query6(int n) {
        String[][] array = new String[n][3];
        List<String> products = this.billing_catalog.getTopMostPurchased(n);
        int[] clients = new int[n];
        List<Integer> units = new ArrayList<>();
        int j = 0;
        for (String p : products) {
            units.add(this.billing_catalog.getProductUnits(p));
            clients[j++] = Arrays.stream(this.branches_catalog.getTotalDistinctsClientsProductMonth(p)).sum();
        }
        for (int i = 0; i < n; i++) {
            array[i][0] = products.get(i);
            array[i][1] = String.valueOf(units.get(i));
            array[i][2] = String.valueOf(clients[i]);
        }
        return array;
    }

    /**
     * Determina os 3 maiores compradores de cada filial (a nivel de dinheiro faturado)
     * @return Array de Matrizes de strings com o codigo de cliente e total faturado dos 3 maiores compradores para cada filial
     */
    public String[][][] query7() {
        return this.branches_catalog.getTop3BuyersByBranch();
    }

    /**
     * (!!!)
     * @return (!!!)
     */
    public String[][] query8(int n) {
        Map<String, Set<String>> list = this.branches_catalog.getClientsDistinctsProducts();
        Map<String, Integer> _list = list.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e -> e.getValue().size()));
        List<Map.Entry<String, Integer>> clients = new ArrayList<>(_list.entrySet());

        final int[] aux = new int[1];
        Comparator<Map.Entry<String, Integer>> comp = (a, b) ->
                (aux[0] = b.getValue() - a.getValue())
                        == 0 ? a.getKey().compareTo(b.getKey()) : aux[0];

        clients.sort(comp);
        String[][] result = new String[n][2];
        int i = 0;
        for( Map.Entry<String, Integer> c : clients) {
            if( i >= n) break;
            result[i][0] = c.getKey();
            result[i++][1] = String.valueOf(c.getValue());
        }
        return result;
    }

    /**
     * (!!!)
     * @return (!!!)
     */
    public String[][] query9(String product, int n) {
        Map<String, List<Double>> list = this.branches_catalog.getProductAllClients(product);
        List<Map.Entry<String, List<Double>>> clients = new ArrayList<>(list.entrySet());

        final int[] aux = new int[1];
        Comparator<Map.Entry<String, List<Double>>> comp = (a, b) ->
                (aux[0] = (int) (b.getValue().get(0) - a.getValue().get(0)))
                        == 0 ? a.getKey().compareTo(b.getKey()) : aux[0];

        clients.sort(comp);
        String[][] result = new String[n][3];
        int i = 0;
        for( Map.Entry<String, List<Double>> c : clients) {
            if (i >= n) break;
            result[i][0] = c.getKey();
            result[i][1] = String.valueOf(c.getValue().get(0));
            result[i++][2] = String.valueOf(c.getValue().get(1));
        }
        return result;
    }

    /**
     * Determina mes a mes, e para cada mes, filial a filial, a faturacao total com cada produto
     * @return HashMap com codigos de produto e correspondente matriz de faturacao (por meses e por filiais)
     */
    public Map<String, double[][]> query10() {
        return this.billing_catalog.getProductsBillingByMonthAndBranch();
    }

    /**
     * Numero de clientes distintos a comprar cada mes por filial
     * @return Devolve um array multi dimensional de ints com o numero de clientes distintos que compraram num certo mês dividido por filial
     */
    public int[][] getNumberOfDistinctClients(){
        try {
            return this.branches_catalog.getNumberOfDistinctClients();
        }catch (Exception e) {
            return null;
        }
    }

    /**
     * Devolve o numero total de compras por mês
     * @return Devolve um array de inteiros com as compras feitas nos 12 meses do ano
     */
    public int[] getShoppingFrequency(){
        try {
            return this.branches_catalog.getShoppingFrequency();
        }catch (Exception e){
            return null;
        }
    }

    /**
     * Faturação total por mês por filial e global
     * @return Devolve um array multi dimensional de doubles com a faturacao por mes e filial
     */
    public double[][] getBillingByMonthAndBranch(){
        try {
            return this.billing_catalog.getBillingByMonthAndBranch();
        }catch (Exception e){
            e.printStackTrace();
            return null;
        }
    }

    /**
     * Apresenta ao utilizador os dados referentes ao último ficheiro de vendas lido,
     * designadamente, nome do ficheiro, número total de registos de venda errados,
     * número total de produtos, total de diferentes produtos comprados, total de não
     * comprados, número total de clientes e total dos que realizaram compras, total de
     * clientes que nada compraram, total de compras de valor total igual a 0.0 e faturação
     * total.
     * @return String array com o mencionado acima
     */
    public String[] statisticalConsult(){
        int tmp_NumberOfProducts = this.product_catalog.getSize();
        int tmp_ProductsBought = this.branches_catalog.getProductsBought().size();
        int tmp_NumberOfClients = this.client_catalog.getSize();
        int tmp_ClientsWhoDidntBuy = this.branches_catalog.getClientWhoBought();
        String[] result = new String[10];
        result[0] = this.saleFileName; // String
        result[1] = String.valueOf(this.readSales - this.validSales); // int
        result[2] = String.valueOf(tmp_NumberOfProducts); // int
        result[3] = String.valueOf(tmp_ProductsBought); // int
        result[4] = String.valueOf(tmp_NumberOfProducts - tmp_ProductsBought); // int
        result[5] = String.valueOf(tmp_NumberOfClients); // int
        result[6] = String.valueOf(tmp_ClientsWhoDidntBuy); // int
        result[7] = String.valueOf(tmp_NumberOfClients - tmp_ClientsWhoDidntBuy); //int
        result[8] = String.valueOf(billing_catalog.getGiveawaysAmount());//int
        result[9] = String.valueOf(billing_catalog.getTotalBilledSum()); //double
        return result;
    }

    public int getClientsSize(){
        return this.client_catalog.getSize();
    }

    public int getProductsSize(){
        return this.product_catalog.getSize();
    }

    public int getReadSales() {
        return readSales;
    }

    public int getValidSales() {
        return validSales;
    }

    public int getReadProducts() {
        return readProducts;
    }

    public int getReadClients() {
        return readClients;
    }

    /**
     * Guarda o estado atual do Model para um dado ficheiro
     * @param path Caminho do ficheiro a guardar
     * @throws IOException Exceção de erro a escrever para o ficheiro
     */
    public void save(String path) throws IOException {
        FileOutputStream a = new FileOutputStream(path);
        ObjectOutputStream r = new ObjectOutputStream(a);
        r.writeObject(this);
        r.flush();
        r.close();
    }

    /**
     * Carrega o Model de um ficheiro de ObjectStream
     * @param path Caminho do ficheiro a carregar
     * @return Modelo lido
     * @throws IOException Erro a ler do ficheiro
     * @throws ClassNotFoundException O ficheiro lido é invalido
     */
    public static GestVendasModel load(String path) throws IOException, ClassNotFoundException {
        FileInputStream r = new FileInputStream(path);
        ObjectInputStream a = new ObjectInputStream(r);
        GestVendasModel u = (GestVendasModel) a.readObject();
        a.close();
        return u;
    }
}
