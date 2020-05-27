package model;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

import static Utils.Constants.N_BRANCHES;
import static Utils.Constants.N_MONTHS;

public class GestVendasModel implements IGestVendasModel {

    private IClientCatalog client_catalog; /**< Cátalogo de clientes */
    private final IProductCatalog product_catalog; /**< Cátalogo de produto */
    private final IBillingCatalog billing_catalog; /**< Cátalogo de faturação */
    private final IBranchCatalog branches_catalog; /**< Cátalogo de filiais */
    private int readClients;
    private int readProducts;
    private int readSales;
    private int validSales;

    public GestVendasModel(){
        this.client_catalog = new ClientCatalog();
        this.product_catalog = new ProductCatalog();
        this.billing_catalog = new BillingCatalog();
        this.branches_catalog = new BranchCatalog();
        this.readClients = 0;
        this.readProducts = 0;
        this.readSales = 0;
        parseClients();
        parseProducts();
        parseSales();
    }

    public void parseClients() {
        File file = new File("data/Clientes.txt");

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String clientCode = null;

            while ((clientCode = reader.readLine()) != null) {
                this.client_catalog.insertClient(clientCode);
                this.readClients++;
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not Found!");
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void parseProducts() {
        File file = new File("data/Produtos.txt");

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String productCode = null;

            while ((productCode = reader.readLine()) != null) {
                if (this.product_catalog.insertProduct(productCode)) {
                    this.billing_catalog.addBillingProduct(productCode);
                }
                this.readProducts++;
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not Found!");
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public void parseSales() {
        File file = new File("data/Vendas_1M.txt");

        List<String> lista_vendas = new ArrayList<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String sale_line = null;

            while ((sale_line = reader.readLine()) != null) {
                lista_vendas.add(sale_line);
            }
            this.readSales = lista_vendas.size();
            lista_vendas
                    .parallelStream()
                    .map(Sale::new)
                    .filter(e -> this.client_catalog.existClient(e.getClient())
                            && this.product_catalog.existProduct(e.getProduct()))
                    .collect(Collectors.toList())
                    .forEach(e -> {this.billing_catalog.updateBillings(e); this.branches_catalog.updateBranches(e); this.validSales++;});

        } catch (FileNotFoundException e) {
            System.out.println("File not Found!");
            e.printStackTrace();
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

    public String[][] query6(int n) {
        String[][] array = new String[n][3];
        System.out.println("x");
        List<String> products = this.billing_catalog.getTopMostPurchased(n);
        System.out.println("x");
        int[] clients = new int[n];
        List<Integer> units = new ArrayList<>();
        int j = 0;
        for (String p : products) {
            System.out.println("teste");
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
     * Query 7: Determina os 3 maiores compradores de cada filial (a nivel de dinheiro faturado)
     * @return Array de Matrizes de strings com o codigo de cliente e total faturado dos 3 maiores compradores para cada filial
     */
    public String[][][] query7() {
        return this.branches_catalog.getTop3BuyersByBranch();
    }

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

    public String[][] query9(String product, int n) {
        Map<String, List<Double>> list = this.branches_catalog.getProductAllClients(product);
        List<Map.Entry<String, List<Double>>> clients = new ArrayList<>(list.entrySet());

        final int[] aux = new int[1];
        Comparator<Map.Entry<String, List<Double>>> comp = (a, b) ->
                (aux[0] = (int) (b.getValue().get(0) - a.getValue().get(0)))
                        == 0 ? a.getKey().compareTo(b.getKey()) : aux[0];

        clients.sort(comp);
        String[][] result = new String[clients.size()][3];
        int i = 0;
        for( Map.Entry<String, List<Double>> c : clients) {
            result[i][0] = c.getKey();
            result[i][1] = String.valueOf(c.getValue().get(0));
            result[i++][2] = String.valueOf(c.getValue().get(1));
        }
        return result;

    }

    /**
     * Query 10: Determina mes a mes, e para cada mes, filial a filial, a faturacao total com cada produto
     * @return HashMap com codigos de produto e correspondente matriz de faturacao (por meses e por filiais)
     */
    public Map<String, double[][]> query10() {
        return this.billing_catalog.getProductsBillingByMonthAndBranch();
    }


    /**
     * Devolve o numero total de compras por mês, faturação total por mês por filial e global, numero de clientes distintos a comprar cada mes por filial
     */
    public void ce2() {
        int[] shoppingFrequency;
        try{
            shoppingFrequency = this.branches_catalog.getShoppingFrequency();
            for (int i : shoppingFrequency)
                System.out.println(i);
        } catch (Exception e) {
            //e.printStackTrace();
        }
    }

    public void startSGV() throws IOException {
        parseClients();
        parseProducts();
        parseSales();
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
}
