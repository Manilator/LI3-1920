package model;

public interface IBillingProduct {

    public void updateBillingProduct(double totalBilled, int unities, char promotion_type, int branch, int month);

    public int[] getN_sales();

    public double[] getTotalBilled();

    public int getTotalUnits();

    public double[][] getBranchesBilled();
}
