package model;

import java.util.Map;

public interface IBranchCatalog {

    void updateBranches(ISale sale);

    /**
     * Hashtable com todos os códigos de todos os produtos que efetuaram compras em pelo menos uma filial
     * @return Map com códigos de produtos como valores e chaves
     */
    Map<String,String> getProductsBought();

    int distinctClientsMonth(int month, int branch);

    int[] getTotalDistinctsClientsProductMonth(String product);
}
