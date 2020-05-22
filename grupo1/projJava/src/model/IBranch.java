package model;

import java.util.Map;

public interface IBranch {

    public void updateBranch(String client_code, String product_code, int units, char promotion_type, double billed, int month);

    Map<String, String> getProductsNeverBought(Map<String, String> productsBought);

    public int distinctClientsMonth(int month);

    public int[] getDistinctsClientsProductMonth(String product);

    /**
     * Query 7: Determina numa dada filial os 3 maiores compradores (a nivel de dinheiro faturado)
     * @return Matriz de strings com o codigo de cliente e total faturado dos 3 maiores compradores dessa filial
     */
    public String[][] getTop3BuyersInBranchX();
}
