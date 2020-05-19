package model;

public interface IBilling {

    public void updateBilling(String code, double totalBilled, int unities, char promotion_type, int branch);
}
