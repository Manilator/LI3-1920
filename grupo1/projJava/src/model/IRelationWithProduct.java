package model;

import java.util.Set;

public interface IRelationWithProduct {

    void updateRelationWithProduct(String product_code, int quantity, double billed, int month);

    boolean didPurchaseMonth(int month);

    /**
     * Get amount of distinct products that bought in each month
     * @return Array of ints with amount of distinct products bought
     */
    int[] getAmountDistinctInfoProducts();

    /**
     * Get amount the amount billed each month
     * @return Array of ints with the amount billed each month
     */
    double[] getTotalBilled();

    public boolean didPurchaseMonth(int month);

    /**
     * Devolve a soma do total faturado de todos os meses
     * @return Valor total faturado
     */
    public double getSumTotalBilled();

    /**
     * Get amount of sales made at each month
     * @return Array of ints with the amount of sales in each month
     */
    int[] getN_sales();

    public Set<String> getTotalDistinctProducts();
}
