package model;

public interface IRelationWithProduct {

    public void updateRelationWithProduct(String product_code, int quantity, double billed, int month);

    public boolean didPurchaseMonth(int month);

}
