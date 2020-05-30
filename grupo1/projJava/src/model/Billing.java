package model;

import java.io.Serializable;
import java.util.Arrays;

import static Utils.Constants.N_BRANCHES;

public class Billing implements IBilling, Serializable {

    private static final long serialVersionUID = 2537488678609275391L;
    private int n_sales; /**< Número de Vendas */
    private double totalBilled; /**< Total faturado */
    private int unitiesP; /**< Unidades P vendidas */
    private int unitiesN; /**< Unidades N vendidas */
    private int[] branchesUnities; /**< Número de unidades vendidas dividida por filiais */
    private double[] branchesBilling; /**< Faturação dividida por filiais */
    private int[] branchesNSales; /**< Número de vendas dividida por filiais */
    private int giveaways;

    /**
     * Construtos vazio da class Billing
     */
     Billing() {
        this.n_sales = 0;
        this.totalBilled = 0;
        this.unitiesP = 0;
        this.unitiesN = 0;
        this.giveaways = 0;
        this.branchesUnities = new int[N_BRANCHES];
        this.branchesBilling = new double[N_BRANCHES];
        this.branchesNSales = new int[N_BRANCHES];
        initBranches();
    }

    /**
     * Funcao auxiliar que preenche os valores dos arrays das variaveis da classe
     */
    private void initBranches() {
            Arrays.fill(this.branchesBilling, 0);
            Arrays.fill(this.branchesNSales, 0);
            Arrays.fill(this.branchesUnities, 0);
    }

    /**
     * Atualiza a classe billing
     * @param totalBilled Quantidade faturada
     * @param unities Numero de unidades compradas
     * @param promotion_type Tipo de promocao utilizada
     * @param branch Filial escolhida
     */
    public void updateBilling(double totalBilled, int unities, char promotion_type, int branch) {

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
        if(totalBilled == 0)
            this.giveaways++;
    }

    /**
     * Get do numero de vendas total
     * @return Devolve o int do numero de vendas total
     */
    public int getN_sales() {
        return n_sales;
    }

    /**
     * Get do numero de vendas numa certa filial
     * @param branch Numero da filial
     * @return Devolve o int do numero de vendas numa certa filial
     */
    public int getN_sales(int branch) {
         return branchesNSales[branch-1];
    }

    /**
     * Get do numero de vendas a preco 0
     * @return Devolve a quantidade de produtos com venda a 0
     */
    public int getGiveaways(){return this.giveaways;}

    /**
     * Quantidade total faturada
     * @return Devolve um double com a quantidade faturada total
     */
    public double getTotalBilled() {
        return this.totalBilled;
    }
}
