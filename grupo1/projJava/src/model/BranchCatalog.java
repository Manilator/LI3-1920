package model;

import java.util.*;
import java.util.stream.Collectors;

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

    /**
     * Dado um código de cliente retorna uma lista ordenada com os códigos de produtos mais comprados pelo mesmo em todas as filiais
     * @param clientCode String com o código do cliente
     * @return Lista de strings com códigos de produtos mais comprados nas filiais
     */
    public String[][] getClientsFavoriteProducts(String clientCode){

        Map<String,Integer> productsBought = new LinkedHashMap<>();

        for (int branch = 0; branch < N_BRANCHES; branch++)
            productsBought = this.branches[branch].getClientsFavoriteProductsBranch(clientCode, productsBought);

        List<Map.Entry<String, Integer>> clients = new ArrayList<>(productsBought.entrySet());

        final int[] aux = new int[1];
        Comparator<Map.Entry<String, Integer>> comp = (a, b) ->
                (aux[0] = b.getValue() - a.getValue())
                        == 0 ? a.getKey().compareTo(b.getKey()) : aux[0];

        clients.sort(comp);
        String[][] result = new String[clients.size()][2];
        int i = 0;
        for( Map.Entry<String, Integer> c : clients) {
            result[i][0] = c.getKey();
            result[i++][1] = String.valueOf(c.getValue());
        }

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
