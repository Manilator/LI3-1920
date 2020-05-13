package model;

public class BillingProduct {

    private double totalBilledN; /**< Total faturado no tipo N*/
    private double totalBilledP; /**< Total faturado no tipo P*/
    private int unitiesP; /**< Unidades P vendidas */
    private int unitiesN; /**< Unidades N vendidas */
    private int[][] branchesQnt; /**< Quantdade dividida por filiais e tipo de promoção */
    private double[][] brachesBilled; /**< Faturação dividida por filiais e tipo de promoção */

}
