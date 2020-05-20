package model;

import java.util.Map;

public interface IBranch {

    public void updateBranch(String client_code, String product_code, int units, char promotion_type, double billed, int month);

    /**
     * Hashtable com os códigos de todos os produtos que efetuaram compras na filial
     * @return Map com códigos de produtos como valores e chaves que compraram na filial
     */
    Map<String, String> getProductsBought(Map<String, String> productsBought);

    public int distinctClientsMonth(int month);

    public int[] getDistinctsClientsProductMonth(String product);
}
