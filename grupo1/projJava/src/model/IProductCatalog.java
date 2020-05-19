package model;

import java.util.List;
import java.util.Map;

public interface IProductCatalog {

    public boolean insertProduct(String productCode);

    public boolean existProduct(String code);

    public int getSize();

    List<String> getProductsNotBought(Map<String,String> allProductsBought);
}
