package model;

import java.util.List;
import java.util.Map;

public interface IBranchCatalog {

    public void updateBranches(Sale sale);
    Map<String,String> getProductNeverBought();
}
