package model;

import java.util.Map;
import java.util.Set;

public interface IRelationWithClient {

    public void updateRelationWithClient(String client_code, int units, char promotion_type, int month, double totalbilled);

    public int[] getTotalProductsSold();

    public int[] getDistinctsClientsProductMonth();

    /**
     * Recolhe todos os clientes que compraram o produto
     * @return Set com todas as entradas do Hashmap que contém os clientes que compraram o produto
     */
    public Set<Map.Entry<String, IInfoClient>> getAllClients();
}
