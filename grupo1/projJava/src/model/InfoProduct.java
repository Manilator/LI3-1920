package model;

public class InfoProduct {

    private int[] quantities; /**< Quantidades por cada mês */
    private double[] totalBilled; /**< Faturação total por cada mês */

    public InfoProduct() {
        this.quantities = new int[12];
        this.totalBilled = new double[12];
    }

    public void updateInfoProduct(int quantity, double billed, int month) {
        this.quantities[month-1] += quantity;
        this.totalBilled[month-1] += billed;
    }
}
