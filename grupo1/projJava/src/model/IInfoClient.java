package model;

public interface IInfoClient {

    public void updateInfoClient(int units, char promotion_type, int month, double totalBilled);

    /**
     * Recolhe se um cliente realizou a compra de um produto por mês
     * @return Array de booleanos em que cada entrada corresponde aos meses
     */
    public boolean[] didPurchaseMonth();

    /**
     * Calcula o total gasto
     * @return Total gasto
     */
    public double getTotalBilled();

    /**
     * Calcula o total de unidades
     * @return Total de unidades
     */
    public int getTotalUnits();
}
