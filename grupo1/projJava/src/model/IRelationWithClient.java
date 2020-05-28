package model;

import java.util.Map;
import java.util.Set;

public interface IRelationWithClient {

    void updateRelationWithClient(String client_code, int units, char promotion_type, int month, double totalbilled);

    /**
     * Get da variável que contém a quantidade de produtos que um certo cliente comprou
     * @return Array de ints com a quantidade de produtos que um certo cliente comprou
     */
    int[] getTotalProductsBought();

    int[] getDistinctsClientsProductMonth();

    /**
     * Recolhe todos os clientes que compraram o produto
     * @return Set com todas as entradas do Hashmap que contém os clientes que compraram o produto
     */
    Set<Map.Entry<String, IInfoClient>> getAllClients();
}
