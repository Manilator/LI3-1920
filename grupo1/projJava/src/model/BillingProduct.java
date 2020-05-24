package model;

import java.util.Arrays;

import static Utils.Constants.*;

public class BillingProduct implements IBillingProduct{

    private double[] totalBilledN; /**< Total faturado no tipo N separado por meses*/
    private double[] totalBilledP; /**< Total faturado no tipo P separado por meses*/
    private int[] unitiesP; /**< Unidades P vendidas separado por meses*/
    private int[] unitiesN; /**< Unidades N vendidas separado por meses*/
    private int[][] branchesQnt; /**< Quantidade dividida por mes e filial */
    private double[][] branchesBilled; /**< Faturação dividida por mes e filial */
    private int[] n_sales; /**< Número de vendas separadas por mês */

    BillingProduct() {
        this.totalBilledN = new double[N_MONTHS];
        this.totalBilledP = new double[N_MONTHS];
        this.unitiesP = new int[N_MONTHS];
        this.unitiesN = new int[N_MONTHS];
        this.branchesQnt = new int[N_MONTHS][N_BRANCHES];
        this.branchesBilled = new double[N_MONTHS][N_BRANCHES];
        this.n_sales = new int[N_MONTHS];
        this.initArrays();
    }

    private void initArrays() {
        for (int[] row : this.branchesQnt)
            Arrays.fill(row, 0);
        for (double[] row : this.branchesBilled) {
            Arrays.fill(row, 0);
        }
        Arrays.fill(this.totalBilledN, 0);
        Arrays.fill(this.totalBilledP, 0);
        Arrays.fill(this.unitiesN, 0);
        Arrays.fill(this.unitiesP, 0);
        Arrays.fill(this.n_sales,0);
    }

    public double[] getTotalBilledN() {
        return totalBilledN;
    }

    public double[] getTotalBilledP() {
        return totalBilledP;
    }

    public int[] getUnitiesP() {
        return unitiesP;
    }

    public int[] getUnitiesN() {
        return unitiesN;
    }

    public int[][] getBranchesQnt() {
        return branchesQnt.clone();
    }

    public double[][] getBranchesBilled() {
        return branchesBilled.clone();
    }

    public void updateBillingProduct(double totalBilled, int unities, char promotion_type, int branch, int month) {
        int r = 0;
        if (promotion_type == 'N') {
            this.totalBilledN[month-1] += totalBilled;
            this.unitiesN[month-1] += unities;
            r = 1;
        } else if (promotion_type == 'P') {
            this.totalBilledP[month-1] += totalBilled;
            this.unitiesP[month-1] += unities;
            r = 1;
        }
        this.n_sales[month-1]++;
        this.branchesQnt[month-1][branch-1] += unities;
        this.branchesBilled[month-1][branch-1] += totalBilled;
    }

    public int[] getN_sales() {
        return this.n_sales;
    }

    public double[] getTotalBilled() {
        double[] result = new double[N_MONTHS];
        Arrays.setAll(result, e -> this.totalBilledN[e] + this.totalBilledP[e]);
        return result;
    }

    public int getTotalUnits() {
        return Arrays.stream(unitiesN).sum() + Arrays.stream(unitiesP).sum();
    }

}
