package model;

import java.math.BigDecimal;
import java.util.HashMap;
import java.util.Hashtable;

import static Utils.Constants.N_BRANCHES;

public class BranchCatalog {

    private final Branch[] branches;

    public BranchCatalog() {
        this.branches = new Branch[N_BRANCHES];
        this.initBranchCatalog(N_BRANCHES);
    }

    public Branch[] getBranches() {
        return this.branches.clone();
    }

    public void initBranchCatalog(int n) {
        for (int i = 0; i < n; i++) {
            this.branches[i] = new Branch();
        }
    }

    public void updateBranches(Sale sale) {
        int branch_number = sale.getBranch();
        int units = sale.getUnits();
        Branch exist = this.branches[branch_number-1];
        exist.updateBranch(sale.getClient(), sale.getProduct(), units, sale.getPromotion(), sale.getPrice() * units, sale.getMonth());
    }
}
