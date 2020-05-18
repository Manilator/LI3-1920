package model;

import java.math.BigDecimal;
import java.util.Arrays;
import java.util.HashMap;

import static Utils.Constants.N_MONTHS;

public class BillingCatalog {

    private final Billing[] billings;
    private final HashMap<String, BillingProduct> billingsProduct; /**< Faturação dividida por produtos */

    public BillingCatalog() {
        this.billings = new Billing[N_MONTHS];
        this.billingsProduct = new HashMap<>();
        this.initBillingCatalog();
    }

    public Billing[] getBranches() {
        return  this.billings.clone();
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

    void updateBillings(Sale sale) {
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


    private BillingProduct getBillingProduct(String product_code) {
        return this.billingsProduct.get(product_code);
    }
}
