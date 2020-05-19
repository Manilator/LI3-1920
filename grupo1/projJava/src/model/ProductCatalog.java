package model;

import java.util.*;

import java.util.HashMap;
import java.util.Map;

public class ProductCatalog implements IProductCatalog {

    private Map<String,IProduct> products;


    public ProductCatalog() {
        products = new HashMap<>();
    }


    public boolean insertProduct(String productCode){
        Product product = new Product(productCode);
        if (product.validate()) {
            this.products.put(productCode, product);
            return true;
        }
        return false;
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

    public List<String> getProductsNotBought(Map<String,String> allProductsBought){
        List<String> result = new ArrayList<>();

        for (Map.Entry<String, IProduct> entry : products.entrySet())
            if(!allProductsBought.containsKey(entry.getKey()))
                result.add(entry.getKey());
        Collections.sort(result);
        return result;
    }
}
