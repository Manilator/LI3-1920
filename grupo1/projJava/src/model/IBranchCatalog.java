package model;

import java.util.Map;

public interface IBranchCatalog {

    public void updateBranches(Sale sale);

    Map<String,String> getProductNeverBought();

    public int distinctClientsMonth(int month, int branch);

    public int[] getTotalDistinctsClientsProductMonth(String product);
}
