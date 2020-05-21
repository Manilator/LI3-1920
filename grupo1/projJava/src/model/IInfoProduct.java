package model;

public interface IInfoProduct {

    public void updateInfoProduct(int quantity, double billed, int month);

    /**
     * Get amount of products bought each month
     * @return Array of ints with the amount of products bought
     */
    int[] getQuantities();
}
