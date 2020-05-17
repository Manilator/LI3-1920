package model;

import java.lang.reflect.Array;
import java.math.BigDecimal;
import java.util.Arrays;

import static Utils.Constants.*;

public class BillingProduct {

    private double totalBilledN; /**< Total faturado no tipo N*/
    private double totalBilledP; /**< Total faturado no tipo P*/
    private int unitiesP; /**< Unidades P vendidas */
    private int unitiesN; /**< Unidades N vendidas */
    private int[][] branchesQnt; /**< Quantdade dividida por filiais e tipo de promoção */
    private double[][] brachesBilled; /**< Faturação dividida por filiais e tipo de promoção */

    BillingProduct() {
        this.totalBilledN = 0;
        this.totalBilledP = 0;
        this.unitiesP = 0;
        this.unitiesN = 0;
        this.branchesQnt = new int[N_BRANCHES][N_TYPES];
        this.brachesBilled = new double[N_BRANCHES][N_TYPES];
        this.initBranches();
    }

    private void initBranches() {
        for (int[] row : this.branchesQnt)
            Arrays.fill(row, 0);
        for (double[] row : this.brachesBilled) {
            Arrays.fill(row, 0);
        }
    }

    public double getTotalBilledN() {
        return totalBilledN;
    }

    public double getTotalBilledP() {
        return totalBilledP;
    }

    public int getUnitiesP() {
        return unitiesP;
    }

    public int getUnitiesN() {
        return unitiesN;
    }

    public int[][] getBranchesQnt() {
        return branchesQnt.clone();
    }

    public double[][] getBrachesBilled() {
        return brachesBilled.clone();
    }

    int updateBillingProduct(double totalBilled, int unities, char promotion_type, int branch) {
        int r = 0;
        if (promotion_type == 'N') {
            this.totalBilledN += totalBilled;
            this.unitiesN += unities;
            this.brachesBilled[branch-1][N] += totalBilled;
            this.branchesQnt[branch-1][N] += unities;
            r = 1;
        } else if (promotion_type == 'P') {
            this.totalBilledP += totalBilled;
            this.unitiesP += unities;
            this.brachesBilled[branch-1][P] += totalBilled;
            this.branchesQnt[branch-1][P] += unities;
            r = 1;
        }
        return r;
    }

}
