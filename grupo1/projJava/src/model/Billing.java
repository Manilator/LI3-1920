package model;

import javax.swing.*;
import java.math.BigDecimal;
import java.util.*;

import static Utils.Constants.N_BRANCHES;

public class Billing {

    private int n_sales; /**< Número de Vendas */
    private double totalBilled; /**< Total faturado */
    private int unitiesP; /**< Unidades P vendidas */
    private int unitiesN; /**< Unidades N vendidas */
    private int[] branchesUnities; /**< Número de unidades vendidas dividida por filiais */
    private double[] branchesBilling; /**< Faturação dividida por filiais */
    private int[] branchesNSales; /**< Número de vendas dividida por filiais */


     Billing() {
        this.n_sales = 0;
        this.totalBilled = 0;
        this.unitiesP = 0;
        this.unitiesN = 0;
        this.branchesUnities = new int[N_BRANCHES];
        this.branchesBilling = new double[N_BRANCHES];
        this.branchesNSales = new int[N_BRANCHES];
         initBranches();
    }

    private void initBranches() {
            Arrays.fill(this.branchesBilling, 0);
            Arrays.fill(this.branchesNSales, 0);
            Arrays.fill(this.branchesUnities, 0);
    }

    public double getTotalBilled() {
        return this.totalBilled;
    }

    public void updateBilling(String code, double totalBilled, int unities, char promotion_type, int branch) {

        this.n_sales++;
        this.totalBilled += totalBilled;
        if(promotion_type == 'N') {
            this.unitiesN += unities;
        } else if (promotion_type == 'P') {
            this.unitiesP += unities;
        }
        this.branchesNSales[branch-1]++;
        this.branchesUnities[branch-1] += unities;
        this.branchesBilling[branch-1] += totalBilled;
    }

}
