package model;

import java.util.*;

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

    /**
     * Função que inicializa as estruturas das filiais
     * @param n número de filiais
     */
    public void initBranchCatalog(int n) {
        for (int i = 0; i < n; i++) {
            this.branches[i] = new Branch();
        }
    }

    /**
     * Função que atualiza as filiais com as informações de uma venda
     * @param sale venda com as informações a serem adicionadas às filiais
     */
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

    /**
     * @param month mês no qual o número de clientes distintos realizaram compras
     * @return Total de clientes distintos que realizaram compras nas diferentes filiais no mês dado
     */
    public int distinctClientsMonth(int month) {
        Set<String> list = new HashSet<>();
        int total = 0;
        for(int i = 0; i < N_BRANCHES; i++)
            list.addAll(this.branches[i].getClientsWithPurchasesMonth(month));
        return list.size();
    }

    /**
     * @param product Produto qual os clientes distintos compraram
     * @return Array de inteiros com os clientes distintos que compraram certo produto
     */
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

    /**
     * Query 7: Determina os 3 maiores compradores de cada filial (a nivel de dinheiro faturado)
     * @return Array de Matrizes de strings com o codigo de cliente e total faturado dos 3 maiores compradores para cada filial
     */
    public String[][][] getTop3BuyersByBranch() {
        String[][][] result = new String[N_BRANCHES][3][2];
        for(int i = 0; i < N_BRANCHES; i++) {
            result[i] = this.branches[i].getTop3BuyersInBranchX();
        }
        return result;
    }

    /*
     * Função que recolhe a lista de clientes e associado a eles um set de códigos de produtos que comprou
     * @return Map com códigos de clientes e associados a eles um Set de códigos de produtos
     */
    public Map<String, Set<String>> getClientsDistinctsProducts() {
        Map<String, Set<String>> list = new HashMap<>();
        for(IBranch b : this.branches) {
            Map<String, Set<String>> clients = b.getClientsDistinctProducts();
            for (Map.Entry<String, Set<String>> c : clients.entrySet()) {
                String client = c.getKey();
                Set<String> products = c.getValue();
                if (!list.containsKey(client))
                    list.put(client,c.getValue());
                else {
                    Set<String> _products = new HashSet<>();
                    _products.addAll(products);
                    _products.addAll(list.get(client));
                    list.replace(client, _products);
                }
            }
        }
        return list;
    }

    /**
     * Recolhe todos os clientes que compraram o produto com unidades e gastos totais
     * @param product Código do produto
     * @return Map com todos os clientes que compraram o produto e associado a cada um o total de unidades e total gasto
     */
    public Map<String, List<Double>> getProductAllClients(String product) {
        Map<String, List<Double>> list = new HashMap<>();
        for(IBranch b : this.branches) {
            Set<Map.Entry<String, IInfoClient>> clients = b.getProductAllClients(product);
            for(Map.Entry<String, IInfoClient> c : clients) {
                String key = c.getKey();
                IInfoClient value = c.getValue();
                List<Double> value_list = new ArrayList<>();
                value_list.add((double) value.getTotalUnits());
                value_list.add(value.getTotalBilled());

                if(!list.containsKey(key))
                    list.put(key, value_list);
                else {
                    List<Double> old = list.get(key);
                    List<Double> value_new = new ArrayList<>();
                    value_new.add(old.get(0) + value_list.get(0));
                    value_new.add(old.get(1) + value_list.get(1));
                    list.replace(key,value_new);
                }
            }
        }
        return list;
    }
}
