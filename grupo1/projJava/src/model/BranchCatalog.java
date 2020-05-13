package model;

import java.util.Hashtable;

public class BranchCatalog {

    private final Hashtable<Integer,Branch> branches;

    public BranchCatalog() {
        this.branches = new Hashtable<>();
    }

    public BranchCatalog getBranches() {
        return (BranchCatalog) this.branches.clone();
    }

    public void initBranchCatalog(int n) {
        for (int i = 0; i < n; i++) {
            this.branches.put(i, new Branch());
        }
    }
}
