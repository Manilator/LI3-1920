package model;

import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

import static Utils.Constants.N_MONTHS;

public class BillingCatalog implements IBillingCatalog{

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

    public List<String> getTopMostPurchased(int n) {
        final int[] aux = new int[1];
        Comparator<Map.Entry<String,IBillingProduct>> c =
                (a,b) -> (aux[0] = b.getValue().getTotalUnits() - a.getValue().getTotalUnits()) == 0 ? a.getKey().compareTo(b.getKey()) : aux[0];
        List<String> sorted = this.billingsProduct
                .entrySet().parallelStream()
                .sorted(c)
                .map(Map.Entry::getKey)
                .collect(Collectors.toList());

        return sorted.subList(0,n);
    }

    public int getProductUnits(String product) {
        return this.billingsProduct.get(product).getTotalUnits();
    }
}
