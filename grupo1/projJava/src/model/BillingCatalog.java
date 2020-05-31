package model;

import java.io.Serializable;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

import static Utils.Constants.N_BRANCHES;
import static Utils.Constants.N_MONTHS;

/**
 * Classe que representa a faturacao
 */
public class BillingCatalog implements IBillingCatalog, Serializable {

    private static final long serialVersionUID = -3319028548749322819L;
    private final IBilling[] billings;
    private final Map<String, IBillingProduct> billingsProduct;

    /**
     * Construtor vazio da classe BillingCatalog
     */
    public BillingCatalog() {
        this.billings = new Billing[N_MONTHS];
        this.billingsProduct = new HashMap<>();
        this.initBillingCatalog();
    }

    /**
     * Funcao auxiliar que inicia variaveis da classe
     */
    public void initBillingCatalog() {
        for (int i = 0; i < N_MONTHS; i++) {
            this.billings[i] = new Billing();
        }
    }

    /**
     * Adiciona um BillingProduct dado um codigo de produto
     * @param code Codigo do produto
     */
    public void addBillingProduct(String code) {
        String _code = code;

        _code = _code.replace("\\r\\n", "");
        if (!this.billingsProduct.containsKey(_code)) {
            this.billingsProduct.put(_code, new BillingProduct());
        }
    }

    /**
     * Atualiza a classe Billings
     * @param sale Classe auxiliar de uma venda
     */
    public void updateBillings(ISale sale) {
        String code = sale.getProduct();
        int month = sale.getMonth();
        double totalBilled = sale.getPrice() * sale.getUnits();
        int unities = sale.getUnits();
        int branch = sale.getBranch();
        char promotion_type = sale.getPromotion();
        this.billings[month-1]
                .updateBilling(totalBilled,
                unities, promotion_type,
                branch);
        this.billingsProduct.get(code).updateBillingProduct(totalBilled, unities, promotion_type, branch, month);
    }

    /**
     * Numero total de vendas com faturacao a 0
     * @return Devolve o numero total de vendas com faturacao 0
     */
    public int getGiveawaysAmount(){
        int result = 0;
        for (int month = 0; month < N_MONTHS; month++)
            result += this.billings[month].getGiveaways();
        return result;
    }

    /**
     * N Produtos mais comprados
     * @param n Numero de elementos requisitados
     * @return Devolve uma lista com os produtos mais comprados
     */
    public List<String> getTopMostPurchased(int n) {
        final int[] aux = new int[1];
        Comparator<Map.Entry<String,IBillingProduct>> c =
                (a,b) -> (aux[0] = b.getValue().getTotalUnits() - a.getValue().getTotalUnits()) == 0 ? a.getKey().compareTo(b.getKey()) : aux[0];
        List<String> sorted = this.billingsProduct
                .entrySet()
                .stream()
                .sorted(c)
                .map(Map.Entry::getKey)
                .collect(Collectors.toList());

        return sorted.subList(0,n);
    }

    /**
     * Determina mes a mes, e para cada mes, filial a filial, a faturacao total com cada produto
     * @return HashMap com codigos de produto e correspondente matriz de faturacao (por meses e por filiais)
     */
    public Map<String, double[][]> getProductsBillingByMonthAndBranch() {
        return this.billingsProduct
                .entrySet()
                .stream()
                .collect(Collectors
                        .toMap(Map.Entry::getKey, e -> e.getValue().getBranchesBilled()));
    }

    /**
     * Faturacao por mes e por filial
     * @return Devolve um array multi dimensional de doubles com a faturacao por mes e filial
     */
    public double[][] getBillingByMonthAndBranch(){
        double[][] result = new double[N_MONTHS][N_BRANCHES];
        for (String key : this.billingsProduct.keySet()){
            double[][] tmp = this.billingsProduct.get(key).getBranchesBilled();
            for (int month = 0; month < N_MONTHS; month++)
                for (int branch = 0; branch < N_BRANCHES; branch++ )
                    result[month][branch] += tmp[month][branch];
        }
        return result;
    }

    /**
     * Numero de vendas de uma dada filial num certo mes
     * @param month Mes
     * @param branch Filial
     * @return Devolve o numero de venda da filial no mes escolhido
     */
    public int getTotalSalesMonth(int month, int branch) {
        return this.billings[month-1].getN_sales(branch);
    }

    /**
     * Numero de vendas de um certo produto
     * @param product Codigo de produto
     * @return Devolve um array com o numero de vendas de um produto por mes
     */
    public int[] getNSalesProduct(String product) {
        return this.billingsProduct.get(product).getN_sales().clone();
    }

    /**
     * Valor faturado nas vendas de um certo produto
     * @param product Codigo de produto
     * @return Devolve um array com a quantidade faturada nas vendas de um produto por mes
     */
    public double[] getTotalBilledMonth(String product) {
        return this.billingsProduct.get(product).getTotalBilled();
    }

    /**
     * Total faturado em todos os meses
     * @return Devolve a quantidade total faturada
     */
    public double getTotalBilledSum() {
        int result = 0;
        for (int month = 0; month < N_MONTHS; month++)
            result += billings[month].getTotalBilled();
        return result;
    }

    /**
     * Numero de produtos comprados
     * @param product Codigo de produto
     * @return Devolve o numero de produtos comprados
     */
    public int getProductUnits(String product) {
        return this.billingsProduct.get(product).getTotalUnits();
    }
}
