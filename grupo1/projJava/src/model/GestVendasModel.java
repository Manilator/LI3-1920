package model;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

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

    public List<String> query1() {
        Map<String,String> allProductsBought = this.branches_catalog.getProductNeverBought();
        return this.product_catalog.getProductsNotBought(allProductsBought);
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
