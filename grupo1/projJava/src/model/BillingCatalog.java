package model;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

import static Utils.Constants.N_BRANCHES;
import static Utils.Constants.N_MONTHS;

public class BillingCatalog implements IBillingCatalog, Serializable {

    private static final long serialVersionUID = -3319028548749322819L;
    private final IBilling[] billings;
    private final Map<String, IBillingProduct> billingsProduct; /**< Faturação dividida por produtos */

    public BillingCatalog() {
        this.billings = new Billing[N_MONTHS];
        this.billingsProduct = new HashMap<>();
        this.initBillingCatalog();
    }

    public IBilling[] getBillings() {
        return billings;
    }

    public void initBillingCatalog() {
        for (int i = 0; i < N_MONTHS; i++) {
            this.billings[i] = new Billing();
        }
    }

    public void addBillingProduct(String code) {
        String _code = code;

        _code = _code.replace("\\r\\n", "");
        if (!this.billingsProduct.containsKey(_code)) {
            this.billingsProduct.put(_code, new BillingProduct());
        }
    }

    public void updateBillings(ISale sale) {
        String code = sale.getProduct();
        int month = sale.getMonth();
        double totalBilled = sale.getPrice() * sale.getUnits();
        int unities = sale.getUnits();
        int branch = sale.getBranch();
        char promotion_type = sale.getPromotion();
        this.billings[month-1]
                .updateBilling(code,
                totalBilled,
                unities, promotion_type,
                branch);
        this.billingsProduct.get(code).updateBillingProduct(totalBilled, unities, promotion_type, branch, month);
    }


    private IBillingProduct getBillingProduct(String product_code) {
        return this.billingsProduct.get(product_code);
    }

    public int getTotalSalesMonth(int month) {
        return this.billings[month-1].getN_sales();
    }

    public int getTotalSalesMonth(int month, int branch) {
        return this.billings[month-1].getN_sales(branch);
    }

    public int[] getNSalesProduct(String product) {
        return this.billingsProduct.get(product).getN_sales();
    }

    public double[] getTotalBilledMonth(String product) {
        return this.billingsProduct.get(product).getTotalBilled();
    }

    public double getTotalBilledSum() {
        int result = 0;
        for (int month = 0; month < N_MONTHS; month++)
            result += billings[month].getTotalBilled();
        return result;
    }

    public int getGiveawaysAmount(){
        int result = 0;
        for (int month = 0; month < N_MONTHS; month++)
            result += this.billings[month].getGiveaways();
        return result;
    }

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

    public int getProductUnits(String product) {
        return this.billingsProduct.get(product).getTotalUnits();
    }

    /**
     * Query 10: Determina mes a mes, e para cada mes, filial a filial, a faturacao total com cada produto
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
}
