package model;

import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Interface da classe que representam todas as filiais
 */
public interface IBranchCatalog {

    /**
     * Função que atualiza as filiais com as informações de uma venda
     * @param sale venda com as informações a serem adicionadas às filiais
     */
    void updateBranches(ISale sale);

    /**
     * Hashtable com todos os códigos de todos os produtos que efetuaram compras em pelo menos uma filial
     * @return Map com códigos de produtos como valores e chaves
     */
    Map<String,String> getProductsBought();

    /**
     * Dado um código de cliente, determinar, para cada mês, quantas compras fez, quantos produtos distintos comprou e quanto gastou no total em todas as filiais
     * @param clientCode Código de cliente
     * @return Array de doubles com numero de compras, produtos distintos e valor total gasto, em cada mês em todas as filiais
     */
    double[][] getClientShoppingLog(String clientCode);
  
    /**
     * Determina os 3 maiores compradores de cada filial (a nivel de dinheiro faturado)
     * @return Array de Matrizes de strings com o codigo de cliente e total faturado dos 3 maiores compradores para cada filial
     */
    String[][][] getTop3BuyersByBranch();

    /**
     * Dado um código de cliente retorna uma lista ordenada com os códigos de produtos mais comprados pelo mesmo em todas as filiais
     * @param clientCode String com o código do cliente
     * @return Lista de strings com códigos de produtos mais comprados nas filiais
     */
    String[][] getClientsFavoriteProducts(String clientCode);

    /**
     * Dado um mês e uma filial retorna o total de clientes distintos que realizaram compras no mês dado na final
     * @param month mês no qual o número de clientes distintos realizaram compras
     * @param branch (MANI)
     * @return Total de clientes distintos que realizaram compras na filial no mês dado
     */
    int distinctClientsMonth(int month, int branch);

    /**
     * Dado um código de produto retorna o total de clientes distintos que compraram este produto separado por meses
     * @param product Produto qual os clientes distintos compraram
     * @return Array de inteiros com os clientes distintos que compraram certo produto
     */
    int[] getTotalDistinctsClientsProductMonth(String product);

    /**
     * @param month mês no qual o número de clientes distintos realizaram compras
     * @return Total de clientes distintos que realizaram compras nas diferentes filiais no mês dado
     */
    int distinctClientsMonth(int month);

    /**
     * Função que recolhe a lista de clientes e associado a eles um set de códigos de produtos que comprou
     * @return Map com códigos de clientes e associados a eles um Set de códigos de produtos
     */
    Map<String, Set<String>> getClientsDistinctsProducts();

    /**
     * Recolhe todos os clientes que compraram o produto com unidades e gastos totais
     * @param product Código do produto
     * @return Map com todos os clientes que compraram o produto e associado a cada um o total de unidades e total gasto
     */
    Map<String, List<Double>> getProductAllClients(String product);

    /**
     * Calcula o numero total de compras por mês e devolve os resultados
     * @return Devolve um array de inteiros com as compras feitas nos 12 meses do ano
     * @throws Exception Caso alguma informação esteja corrompida este devolve o erro
     */
    int[] getShoppingFrequency() throws Exception;

    /**
     * A quantidade de clientes distintos que compraram num certo mês num conjunto de filiais
     * @return Devolve um array multi dimensional de ints com o numero de clientes distintos que compraram num certo mês dividido por filial
     */
    int[][] getNumberOfDistinctClients();

    /**
     * Numero de clientes que compraram
     * @return Numero de clientes que compraram
     */
    int getClientWhoBought();
}
