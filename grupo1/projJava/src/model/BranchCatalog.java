package model;

import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.Map;

import static Utils.Constants.N_BRANCHES;
import static Utils.Constants.N_MONTHS;

public class BranchCatalog implements IBranchCatalog {

    private final IBranch[] branches;

    public BranchCatalog() {
        this.branches = new Branch[N_BRANCHES];
        this.initBranchCatalog(N_BRANCHES);
    }

    public IBranch[] getBranches() {
        return this.branches.clone();
    }

    public void initBranchCatalog(int n) {
        for (int i = 0; i < n; i++) {
            this.branches[i] = new Branch();
        }
    }

    public void updateBranches(ISale sale) {
        int branch_number = sale.getBranch();
        int units = sale.getUnits();
        this.branches[branch_number-1].updateBranch(sale.getClient(), sale.getProduct(), units, sale.getPromotion(), sale.getPrice() * units, sale.getMonth());
    }

    /**
     * Hashtable com todos os códigos de todos os produtos que efetuaram compras em pelo menos uma filial
     * @return Map com códigos de produtos como valores e chaves
     */
    public Map<String,String> getProductsBought() {
        Map<String,String> productsBought = new LinkedHashMap<>();

        for (int branch = 0; branch < N_BRANCHES; branch++)
            productsBought = this.branches[branch].getProductsBought(productsBought);

        return productsBought;
    }

    /**
     * Dado um código de cliente, determinar, para cada mês, quantas compras fez, quantos produtos distintos comprou e quanto gastou no total em todas as filiais
     * @return Array de doubles com numero de compras, produtos distintos e valor total gasto, em cada mês em todas as filiais
     */
    public double[][] getClientShoppingLog(String clientCode){
        double[][] result = new double[N_MONTHS][3];

        for (int branch = 0; branch < N_BRANCHES; branch++)
            result = this.branches[branch].getClientShoppingLog(clientCode, result);

        return result;
    }

    public int distinctClientsMonth(int month, int branch) {
        return this.branches[branch-1].distinctClientsMonth(month);
    }

    public int[] getTotalDistinctsClientsProductMonth(String product) {
        int[][] totals = new int[N_BRANCHES][N_MONTHS];
        for(int i = 0; i < N_BRANCHES; i++) {
            totals[i] = this.branches[i].getDistinctsClientsProductMonth(product);
        }
        int[] result = new int[N_MONTHS];
        Arrays.fill(result,0);
        for(int i = 0; i < N_BRANCHES; i++) {
            for (int j = 0; j < N_MONTHS; j++) {
                result[j] += totals[i][j];
            }
        }
        return result;
    }
}
