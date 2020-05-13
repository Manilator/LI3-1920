package model;

import java.util.Hashtable;

public class ProductCatalog {

    private final Hashtable<String,Product> products;


    public ProductCatalog() {
        products = new Hashtable<>();
    }

    public Hashtable<String, Product> getProducts() {
        return (Hashtable<String, Product>) products.clone();
    }

    public void insertProduct(String productCode){
        this.products.put(productCode, new Product(productCode));
    }

    public Product getProduct(String cod) {
        return this.getProducts().get(cod);
    }

    public int getSize() {
        return this.products.size();
    }
}
