package model;

import java.io.Serializable;
import java.util.Arrays;

import static Utils.Constants.N_BRANCHES;
import static Utils.Constants.N_MONTHS;

/**
 * Classe que representa a faturacao que um produto teve
 */
public class BillingProduct implements IBillingProduct, Serializable {

    private static final long serialVersionUID = -3606213631648419941L;
    private double[] totalBilledN;
    private double[] totalBilledP;
    private int[] unitiesP;
    private int[] unitiesN;
    private int[][] branchesQnt;
    private double[][] branchesBilled;
    private int[] n_sales;

    /**
     * Construtor vazio da classe BillingProduct
     */
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

    /**
     * Funcao auxiliar que inicia variaveis da classe
     */
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

    /**
     * Faturação dividida por mes e filial
     * @return Devolve o clone da variavel
     */
    public double[][] getBranchesBilled() {
        return branchesBilled.clone();
    }

    /**
     * Atualiza a classe BillingProdutct
     * @param totalBilled Faturacao dada
     * @param unities Numero de unidades
     * @param promotion_type Tipo de promocao
     * @param branch Numero de filial
     * @param month Numero do mes
     */
    public void updateBillingProduct(double totalBilled, int unities, char promotion_type, int branch, int month) {
        if (promotion_type == 'N') {
            this.totalBilledN[month-1] += totalBilled;
            this.unitiesN[month-1] += unities;
        } else if (promotion_type == 'P') {
            this.totalBilledP[month-1] += totalBilled;
            this.unitiesP[month-1] += unities;
        }
        this.n_sales[month-1]++;
        this.branchesQnt[month-1][branch-1] += unities;
        this.branchesBilled[month-1][branch-1] += totalBilled;
    }

    /**
     * Numero de vendas em cada mes
     * @return Devolve o numero venda em cada mes
     */
    public int[] getN_sales() {
        return this.n_sales.clone();
    }

    /**
     * A faturacao total em cada mes
     * @return Devolve faturacao total em cada mes
     */
    public double[] getTotalBilled() {
        double[] result = new double[N_MONTHS];
        Arrays.setAll(result, e -> this.totalBilledN[e] + this.totalBilledP[e]);
        return result;
    }

    /**
     * Numero total de unidades
     * @return Devolve o numero total de unidades
     */
    public int getTotalUnits() {
        return Arrays.stream(unitiesN).sum() + Arrays.stream(unitiesP).sum();
    }

}
