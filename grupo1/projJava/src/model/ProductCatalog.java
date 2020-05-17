package model;

import java.util.HashMap;
import java.util.Hashtable;

public class ProductCatalog {

    private final HashMap<String,Product> products;


    public ProductCatalog() {
        products = new HashMap<>();
    }

    public Hashtable<String, Product> getProducts() {
        return (Hashtable<String, Product>) products.clone();
    }

    public boolean insertProduct(String productCode){
        Product product = new Product(productCode);
        if (product.validate()) {
            this.products.put(productCode, product);
            return true;
        }
        return false;
    }

    public Product getProduct(String cod) {
        return this.getProducts().get(cod);
    }

    public int getSize() {
        return this.products.size();
    }

    public boolean existProduct(String code) {
        return this.products.containsKey(code);
    }
}
