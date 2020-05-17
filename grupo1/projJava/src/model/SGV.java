package model;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collector;
import java.util.stream.Collectors;

public class SGV {

    private ClientCatalog client_catalog; /**< Cátalogo de clientes */
    private final ProductCatalog product_catalog; /**< Cátalogo de produto */
    private final BillingCatalog billing_catalog; /**< Cátalogo de faturação */
    private final BranchCatalog branches_catalog; /**< Cátalogo de filiais */
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

    public SGV(){
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
/*
    public void parseSales() {
        File file = new File("data/Vendas_1M.txt");

        List<String> lista_vendas = new ArrayList<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String sale_line = null;

            while ((sale_line = reader.readLine()) != null) {
                Sale new_sale = new Sale(sale_line);

                lista_vendas.add(sale_line);
            }
            this.readSales = lista_vendas.size();

            List<Sale> valid_vendas = new ArrayList<>();
            valid_vendas = lista_vendas
                    .parallelStream()
                    .map(Sale::new)
                    .filter(e -> this.client_catalog.existClient(e.getClient())
                            && this.product_catalog.existProduct(e.getProduct()))
                    .collect(Collectors.toList());
            valid_vendas.forEach(e -> {this.billing_catalog.updateBillings(e); this.branches_catalog.updateBranches(e); this.validSales++;});

        } catch (FileNotFoundException e) {
            System.out.println("File not Found!");
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    */
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
/*
    int parseSales(SGV sgv, StartValues startValues)
    {
        FILE* file_pointer = fopen((startValues->path_sales)->str,"r");
        char * _fileline = g_malloc(sizeof(char)*1024);
        while(fgets(_fileline, 1024, file_pointer) != NULL)
        {
            Sale _new;

            if ((_new = isValidSale(_fileline, sgv->client_catalog, sgv->product_catalog))) {

                updateBillings(sgv->billings, _new);

                updateBranches(sgv->branches, _new);

                startValues->valid_sales++;
                destroySale(_new);
            }
            startValues->read_sales++;
            g_free(_fileline);
            _fileline = g_malloc(sizeof(char)*1024);
        }
        g_free(_fileline);
        fclose(file_pointer);
        return 1;
    }*/

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
