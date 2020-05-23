package model;

import java.util.Arrays;

import static Utils.Constants.N_MONTHS;

public class InfoClient implements IInfoClient {

    private int[] unitsN; /**< Número de unidades do tipo N */
    private int[] unitsP; /**< Número de unidades do tipo P */
    private double totalBilled;


    public InfoClient() {
        this.unitsN = new int[N_MONTHS];
        this.unitsP = new int[N_MONTHS];
        this.totalBilled = 0;
        Arrays.fill(unitsN,0);
        Arrays.fill(unitsP,0);
    }

    public void updateInfoClient(int units, char promotion_type, int month, double totalBilled) {
        if (promotion_type == 'P') {
            this.unitsP[month-1] += units;
        } else if (promotion_type == 'N') {
            this.unitsN[month-1] += units;
        }
        this.totalBilled += totalBilled;
    }

    /**
     * Recolhe se um cliente realizou a compra de um produto por mês
     * @return Array de booleanos em que cada entrada corresponde aos meses
     */
    public boolean[] didPurchaseMonth() {
        boolean[] months = new boolean[N_MONTHS];
        for(int i = 0; i < N_MONTHS; i++) {
            months[i] = this.unitsP[i] != 0 || this.unitsN[i] != 0;
        }
        return months;
    }

    /**
     * Calcula o total gasto
     * @return Total gasto
     */
    public double getTotalBilled() {
        return totalBilled;
    }

    /**
     * Calcula o total de unidades
     * @return Total de unidades
     */
    public int getTotalUnits() {
        return Arrays.stream(unitsN).sum() + Arrays.stream(unitsP).sum();
    }
}
