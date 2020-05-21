package model;

import java.util.List;
import java.util.Map;

public interface IBranch {

    void updateBranch(String client_code, String product_code, int units, char promotion_type, double billed, int month);

    /**
     * Hashtable com os códigos de todos os produtos que efetuaram compras na filial
     * @return Map com códigos de produtos como valores e chaves que compraram na filial
     */
    Map<String, String> getProductsBought(Map<String, String> productsBought);

    /**
     * Dado um código de cliente, determinar, para cada mês na filial, quantas compras fez, quantos produtos distintos comprou e quanto gastou no total
     * @return Array de doubles com numero de compras, produtos distintos e valor total gasto, em cada mês na filial
     */
    double[][] getClientShoppingLog(String clientCode, double[][] shopLog);

    int distinctClientsMonth(int month);

    int[] getDistinctsClientsProductMonth(String product);

    public List<String> getClientsWithPurchasesMonth(int month);
}
