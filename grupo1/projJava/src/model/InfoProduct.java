package model;

import java.math.BigDecimal;
import java.util.Arrays;

import static Utils.Constants.N_MONTHS;

public class InfoProduct implements IInfoProduct {

    private int[] quantities; /**< Quantidades por cada mês */
    private double[] totalBilled; /**< Faturação total por cada mês */

    public InfoProduct() {
        this.quantities = new int[12];
        this.totalBilled = new double[12];
        Arrays.fill(this.totalBilled, 0);
    }

    public void updateInfoProduct(int quantity, double billed, int month) {
        this.quantities[month-1] += quantity;
        this.totalBilled[month-1] += billed;
    }

    /**
     * Devolve o numero de produtos comprados em cada mês
     * @return Array de inteiros com o numero de produtos comprados
     */
    public int[] getQuantities() {
        return quantities;
    }

    /**
     * Devolve a quantidade de compras do produto no ano inteiro
     * @return Int com a quantidade comprada do produto no ano inteiro
     */
    public int getTotalQuantity(){
        int result = 0;

        for (int i=0;i<N_MONTHS;i++)
            result += quantities[i];

        return result;
    }
}
