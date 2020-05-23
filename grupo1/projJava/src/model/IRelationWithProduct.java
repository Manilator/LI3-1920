package model;

import java.util.Map;
import java.util.Set;

public interface IRelationWithProduct {

    void updateRelationWithProduct(String product_code, int quantity, double billed, int month);

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

    Set<String> getTotalDistinctProducts();
}
