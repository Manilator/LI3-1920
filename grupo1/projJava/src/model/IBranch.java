package model;

public interface IBranch {

    public void updateBranch(String client_code, String product_code, int units, char promotion_type, double billed, int month);

}
