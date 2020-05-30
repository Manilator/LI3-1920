package model;

import java.util.List;
import java.util.Map;
import java.util.Set;

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

    /**
     * Dado um código de cliente retorna uma hashtable com os códigos de produtos mais comprados pelo mesmo na filial
     * @param clientCode String com o código do cliente
     * @param productsBought Hashtable com os códigos de produtos mais comprados pelo mesmo em todas as filiais
     * @return Hashtable com os códigos de produtos mais comprados pelo mesmo na filial
     */
    Map<String,Integer> getClientsFavoriteProductsBranch(String clientCode, Map<String,Integer> productsBought);

    /**
     * Query 7: Determina numa dada filial os 3 maiores compradores (a nivel de dinheiro faturado)
     * @return Matriz de strings com o codigo de cliente e total faturado dos 3 maiores compradores dessa filial
     */
    String[][] getTop3BuyersInBranchX();

    int distinctClientsMonth(int month);

    int[] getDistinctsClientsProductMonth(String product);

    List<String> getClientsWithPurchasesMonth(int month);

    Map<String, Set<String>> getClientsDistinctProducts();

    /**
     * Recolhe todos os clientes que compraram o produto
     * @param product Código do produto
     * @return Set com todas as entradas do Hashmap que contém os clientes que compraram o produto
     */
    Set<Map.Entry<String, IInfoClient>> getProductAllClients(String product);

    /**
     * Calcula o numero total de compras por mês de uma dada filial e devolve os resultados
     * @return Devolve um array de inteiros com as compras feitas numa dada filial nos 12 meses do ano
     * @throws Exception Caso alguma informação esteja corrompida este devolve o erro
     */
    int[] getBranchShoppingFrequency(int branch) throws Exception;

    /**
     * A quantidade de clientes distintos que compraram num certo mês numa certa filial
     * @return Devolve um array de ints com o numero de clientes distintos que compraram num certo mês dividido por filial
     */
    int[] getBranchNumberOfDistinctClients(int branch);

    Set<String> getClientWhoBought();
}
