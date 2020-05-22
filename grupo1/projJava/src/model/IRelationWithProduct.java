package model;

public interface IRelationWithProduct {

    public void updateRelationWithProduct(String product_code, int quantity, double billed, int month);

    public double[] getTotalBilled();

    public boolean didPurchaseMonth(int month);

    /**
     * Devolve a soma do total faturado de todos os meses
     * @return Valor total faturado
     */
    public double getSumTotalBilled();

}
