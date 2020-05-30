package model;

public interface IBilling {

    void updateBilling(String code, double totalBilled, int unities, char promotion_type, int branch);

    int getN_sales();

    int getN_sales(int branch);

    int getGiveaways();

    double getTotalBilled();
}
