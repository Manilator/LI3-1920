package model;

public interface IBillingCatalog {

    public void addBillingProduct(String code);

    public void updateBillings(Sale sale);

    public int getTotalSalesMonth(int month);

    public int getTotalSalesMonth(int month, int branch);

}
