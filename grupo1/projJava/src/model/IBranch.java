package model;

import java.util.Map;

public interface IBranch {

    public void updateBranch(String client_code, String product_code, int units, char promotion_type, double billed, int month);
    Map<String, String> getProductsNeverBought(Map<String, String> productsBought);
}
