package model;

import java.util.List;
import java.util.Map;

public interface IBillingCatalog {

    void addBillingProduct(String code);

    void updateBillings(ISale sale);

    int getTotalSalesMonth(int month);

    int getTotalSalesMonth(int month, int branch);

    int[] getNSalesProduct(String product);

    double[] getTotalBilledMonth(String product);

    List<String> getTopMostPurchased(int n);

    int getProductUnits(String product);

    /**
     * Query 10: Determina mes a mes, e para cada mes, filial a filial, a faturacao total com cada produto
     * @return HashMap com codigos de produto e correspondente matriz de faturacao (por meses e por filiais)
     */
    Map<String, double[][]> getProductsBillingByMonthAndBranch();

    /**
     * Faturacao por mes e por filial
     * @return Devolve um array multi dimensional de doubles com a faturacao por mes e filial
     */
    double[][] getBillingByMonthAndBranch();
}
