package model;

import java.math.BigDecimal;
import java.util.HashMap;

import static Utils.Constants.N_MONTHS;

public class BillingCatalog {

    private final Billing[] billings;

    public BillingCatalog() {
        this.billings = new Billing[N_MONTHS];
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
        for (Billing e : this.billings) {
            e.addBillingProduct(code);
        }
    }

    void updateBillings(Sale sale) {
        int mes = sale.getMonth();
        Billing exist = this.billings[mes-1];
        exist.updateBilling(sale.getProduct(), sale.getPrice() * sale.getUnits(), sale.getUnits(), sale.getPromotion(), sale.getBranch());
    }
}
