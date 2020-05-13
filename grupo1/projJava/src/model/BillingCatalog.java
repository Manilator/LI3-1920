package model;

import java.util.Hashtable;

import static Utils.Constants.N_MONTHS;

public class BillingCatalog {

    private final Hashtable<Integer,Billing> billings;

    public BillingCatalog() {
        this.billings = new Hashtable<>();
    }

    public BranchCatalog getBranches() {
        return (BranchCatalog) this.billings.clone();
    }

    public void initBranchCatalog() {
        for (int i = 0; i < N_MONTHS; i++) {
            this.billings.put(i, new Billing());
        }
    }
}
