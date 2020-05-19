package model;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collector;
import java.util.stream.Collectors;

public class GestVendasModel implements IGestVendasModel {

    private IClientCatalog client_catalog; /**< Cátalogo de clientes */
    private final IProductCatalog product_catalog; /**< Cátalogo de produto */
    private final IBillingCatalog billing_catalog; /**< Cátalogo de faturação */
    private final IBranchCatalog branches_catalog; /**< Cátalogo de filiais */
    private int readProducts;
    private int readSales;
    private int validSales;

    /*
    StartValues initStartValues(){
        StartValues startValues = g_malloc(sizeof(struct startValues));

        startValues->path_clients = NULL;
        startValues->path_products = NULL;
        startValues->path_sales = NULL;
        startValues->valid_clients = 0;
        startValues->read_clients = 0;
        startValues->valid_products = 0;
        startValues->read_products = 0;
        startValues->valid_sales = 0;
        startValues->read_sales = 0;
        return startValues;
    }

    void setPathsSV(StartValues startValues, char * clients_path, char * products_path, char * sales_path){
        startValues->path_clients = g_string_new(clients_path);
        startValues->path_products = g_string_new(products_path);
        startValues->path_sales = g_string_new(sales_path);
    }*/

    public GestVendasModel(){
        this.client_catalog = new ClientCatalog();
        this.product_catalog = new ProductCatalog();
        this.billing_catalog = new BillingCatalog();
        this.branches_catalog = new BranchCatalog();
        this.readProducts = 0;
        this.readSales = 0;
    }

    public void parseClients() {
        File file = new File("data/Clientes.txt");

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String clientCode = null;

            while ((clientCode = reader.readLine()) != null) {
                this.client_catalog.insertClient(clientCode);
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not Found!");
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
/*
    public void parseProducts() {
        File file = new File("data/Produtos.txt");
        List<String> produtos = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String productCode = null;

            while ((productCode = reader.readLine()) != null) {
                produtos.add(productCode);
                this.readProducts++;
            }
            produtos
                    .forEach(e -> {
                        if (this.product_catalog.insertProduct(e)) {
                            this.billing_catalog.addBillingProduct(e);
                        }
                    });

        } catch (FileNotFoundException e) {
            System.out.println("File not Found!");
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
*/

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

/*
    public void parseSales() {
        File file = new File("data/Vendas_1M.txt");

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String sale_line = null;

            while ((sale_line = reader.readLine()) != null) {
                Sale new_sale = new Sale(sale_line);
                if (new_sale.validSale() && this.client_catalog.existClient(new_sale.getClient()) && this.product_catalog.existProduct(new_sale.getProduct())) {
                    this.billing_catalog.updateBillings(new_sale);
                    this.branches_catalog.updateBranches(new_sale);
                    this.validSales++;
                }
                this.readSales++;
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not Found!");
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
*/

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

    /*
    public ClientCatalog getClient_catalog() {
        return client_catalog;
    }

    public ProductCatalog getProduct_catalog() {
        return product_catalog;
    }

    public BillingCatalog getBilling_catalog() {
        return billing_catalog;
    }

    public BranchCatalog getBranches_catalog() {
        return branches_catalog;
    }
    */
}
