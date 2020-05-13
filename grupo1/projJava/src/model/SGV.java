package model;

import java.io.*;

public class SGV {

    private final ClientCatalog client_catalog; /**< Cátalogo de clientes */
    private final ProductCatalog product_catalog; /**< Cátalogo de produto */
    private final BillingCatalog billing_catalog; /**< Cátalogo de faturação */
    private final BranchCatalog branches_catalog; /**< Cátalogo de filiais */

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
                this.product_catalog.insertProduct(productCode);
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not Found!");
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /*
    int parseProducts(Products products, Billings bs, StartValues startValues)
    {
        FILE* file_pointer = fopen((startValues->path_products)->str,"r");
        char * _fileline = g_malloc(sizeof(char)*1024);
        while(fgets(_fileline, 1024, file_pointer) != NULL)
        {
            if(addProduct(products,_fileline))
            {
                int month;
                for (month = 1; month < 13; month++) {
                    insertBillingProduct(bs, month, _fileline);
                }
                startValues->valid_products++;
            }
            startValues->read_products++;
            g_free(_fileline);
            _fileline = g_malloc(sizeof(char)*1024);
        }
        g_free(_fileline);
        fclose(file_pointer);
        return 1;
    }

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

    public void startSGV()
    {
        parseClients();
        parseProducts();
        /*parseSales(sgv, sv);*/
    }

    public int getClientsSize(){
        return this.client_catalog.getSize();
    }

    public int getProductsSize(){
        return this.product_catalog.getSize();
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
