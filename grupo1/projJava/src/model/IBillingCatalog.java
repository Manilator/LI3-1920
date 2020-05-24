package model;

import java.util.List;
import java.util.Map;

public interface IBillingCatalog {

    public void addBillingProduct(String code);

    public void updateBillings(ISale sale);

    public int getTotalSalesMonth(int month);

    public int getTotalSalesMonth(int month, int branch);

    public int[] getNSalesProduct(String product);

    public double[] getTotalBilledMonth(String product);

    public List<String> getTopMostPurchased(int n);

    public int getProductUnits(String product);

    /**
     * Query 10: Determina mes a mes, e para cada mes, filial a filial, a faturacao total com cada produto
     * @return HashMap com codigos de produto e correspondente matriz de faturacao (por meses e por filiais)
     */
    public Map<String, double[][]> getProductsBillingByMonthAndBranch();
}
