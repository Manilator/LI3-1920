package model;

import java.util.HashMap;
import java.util.Hashtable;

public class ProductCatalog implements IProductCatalog {

    private HashMap<String,IProduct> products;


    public ProductCatalog() {
        products = new HashMap<>();
    }

    public Hashtable<String, IProduct> getProducts() {
        return (Hashtable<String, IProduct>) products.clone();
    }

    public boolean insertProduct(String productCode){
        Product product = new Product(productCode);
        if (product.validate()) {
            this.products.put(productCode, product);
            return true;
        }
        return false;
    }

    public IProduct getProduct(String cod) {
        return this.getProducts().get(cod);
    }

    public int getSize() {
        return this.products.size();
    }

    public boolean existProduct(String code) {
        return this.products.containsKey(code);
    }

    public void setProducts(HashMap<String, IProduct> products) {
        this.products = products;
    }
}
