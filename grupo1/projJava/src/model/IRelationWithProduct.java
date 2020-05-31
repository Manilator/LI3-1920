package model;

import java.util.Map;
import java.util.Set;

/**
 * Interface da classe que contem o modelo de relacao de um cliente e os varios produtos que este comprou
 */
public interface IRelationWithProduct {

    /**
     * Função que atualiza a estrutura RelationWithProduct com as informações dadas (!!!) confirmar pls
     * @param product_code código do produto
     * @param quantity quantidade comprada a ser somada à estrutura
     * @param billed montante faturado com a compra do produto a ser somada ao total faturado
     * @param month mês que vai determinar a posição onde as informações serão somadas à estrutura
     */
    void updateRelationWithProduct(String product_code, int quantity, double billed, int month);

    /**
     * Resultado da validacao de compra num dado mes
     * @param month Mês
     * @return Devolve um boolean que indica se comprou ou nao num dado mes
     */
    boolean didPurchaseMonth(int month);

    /**
     * Devolve o numero de produtos distintos comprados em cada mês
     * @return Array de ints com a quantidade de produtos distintos comprados em cada mês
     */
    int[] getAmountDistinctInfoProducts();

    /**
     * Deolve o total faturado em cada mês
     * @return Array de ints com o total faturado em cada mês
     */
    double[] getTotalBilled();

    /**
     * Devolve a soma do total faturado de todos os meses
     * @return Valor total faturado
     */
    double getSumTotalBilled();

    /**
     * Devolve a quantidade de vendas feitas em cada mês
     * @return Array de ints com a quantidade de vendas feitas em cada mês
     */
    int[] getN_sales();

    /**
     * Dada uma hashtable com os códigos de produtos atualizar com as quantidades compradas por cada
     * @param productsBought Hashtable com os códigos de produtos mais comprados pelo mesmo em todas as filiais
     * @return Hashtable com os códigos de produtos mais comprados pelo mesmo na filial
     */
    Map<String,Integer> getClientsFavoriteProductsBranch(Map<String,Integer> productsBought);

    /**
     * Get amount of sales made at each month
     * @return Array of ints with the amount of sales in each month
     */
    Set<String> getTotalDistinctProducts();
}
