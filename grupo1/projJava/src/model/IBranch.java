package model;

import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Interface da classe que representa uma filial
 */
public interface IBranch {

    /**
     * Atualiza a classe
     * @param client_code Codigo do cliente
     * @param product_code Codigo de produto
     * @param units Numero de unidades compradas
     * @param promotion_type Tipo de promocao
     * @param billed Quantidade faturada
     * @param month Mes da compra
     */
    void updateBranch(String client_code, String product_code, int units, char promotion_type, double billed, int month);

    /**
     * Hashtable com os códigos de todos os produtos que efetuaram compras na filial
     * @param productsBought Map com códigos de produtos como valores e chaves que compraram na filial
     * @return Map com códigos de produtos como valores e chaves que compraram na filial
     */
    Map<String, String> getProductsBought(Map<String, String> productsBought);

    /**
     * Dado um código de cliente, determinar, para cada mês na filial, quantas compras fez, quantos produtos distintos comprou e quanto gastou no total
     * @param clientCode Código de cliente
     * @param shopLog Array de doubles com numero de compras, produtos distintos e valor total gasto, em cada mês na filial
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
     * Determina numa dada filial os 3 maiores compradores (a nivel de dinheiro faturado)
     * @return Matriz de strings com o codigo de cliente e total faturado dos 3 maiores compradores dessa filial
     */
    String[][] getTop3BuyersInBranchX();

    /**
     * Função que recolhe o número de clientes que realizaram compras num mês dado
     * @param month mês no qual os clientes realizaram compras
     * @return número de clientes distintos que realizaram compras num mês especifico
     */
    int distinctClientsMonth(int month);

    /**
     * Função que recolhe o número de clientes distintos que realizaram compras separado por meses
     * @param product produto que se pretende obter o número de clientes distintos que o compraram
     * @return Array de inteiros que correspondem ao número de clientes distintos que compraram certo produto separado por meses
     */
    int[] getDistinctsClientsProductMonth(String product);

    /**
     * Função que recolhe a lista de clientes que realizaram compras num certo mês
     * @param month mês no qual os clientes realizaram compras
     * @return Lista de códigos de clientes que realizaram compras no mês
     */
    List<String> getClientsWithPurchasesMonth(int month);

    /**
     * Função que recolhe a lista de clientes e associado a eles um set de códigos de produtos que comprou
     * @return Map com códigos de clientes e associados a eles um Set de códigos de produtos
     */
    Map<String, Set<String>> getClientsDistinctProducts();

    /**
     * Recolhe todos os clientes que compraram o produto
     * @param product Código do produto
     * @return Set com todas as entradas do Hashmap que contém os clientes que compraram o produto
     */
    Set<Map.Entry<String, IInfoClient>> getProductAllClients(String product);

    /**
     * Calcula o numero total de compras por mês de uma dada filial e devolve os resultados
     * @param branch Número da filial
     * @return Devolve um array de inteiros com as compras feitas numa dada filial nos 12 meses do ano
     * @throws Exception Caso alguma informação esteja corrompida este devolve o erro
     */
    int[] getBranchShoppingFrequency(int branch) throws Exception;

    /**
     * A quantidade de clientes distintos que compraram num certo mês numa certa filial
     * @param branch Número da filial
     * @return Devolve um array de ints com o numero de clientes distintos que compraram num certo mês dividido por filial
     */
    int[] getBranchNumberOfDistinctClients(int branch);

    /**
     * Clientes que nunca compraram
     * @return Devolve um Set com os clientes que nunca fizeram compras
     */
    Set<String> getClientWhoBought();
}
