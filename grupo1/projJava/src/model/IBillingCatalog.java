package model;

public interface IBillingCatalog {

    public void addBillingProduct(String code);

    public void updateBillings(ISale sale);

    public int getTotalSalesMonth(int month);

    public int getTotalSalesMonth(int month, int branch);

    public int[] getNSalesProduct(String product);

    public double[] getTotalBilledMonth(String product);

}
