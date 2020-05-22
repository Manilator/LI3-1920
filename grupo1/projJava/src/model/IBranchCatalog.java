package model;

import java.util.Map;
import java.util.Set;

public interface IBranchCatalog {

    void updateBranches(ISale sale);

    /**
     * Hashtable com todos os códigos de todos os produtos que efetuaram compras em pelo menos uma filial
     * @return Map com códigos de produtos como valores e chaves
     */
    Map<String,String> getProductsBought();

    /**
     * Dado um código de cliente, determinar, para cada mês, quantas compras fez, quantos produtos distintos comprou e quanto gastou no total em todas as filiais
     * @return Array de doubles com numero de compras, produtos distintos e valor total gasto, em cada mês em todas as filiais
     */
    double[][] getClientShoppingLog(String clientCode);

    int distinctClientsMonth(int month, int branch);

    int[] getTotalDistinctsClientsProductMonth(String product);

    public int distinctClientsMonth(int month);

    public Map<String, Set<String>> getClientsDistinctsProducts();
}
