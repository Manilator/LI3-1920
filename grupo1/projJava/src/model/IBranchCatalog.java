package model;

import java.util.Map;

public interface IBranchCatalog {

    public void updateBranches(ISale sale);

    Map<String,String> getProductNeverBought();

    public int distinctClientsMonth(int month, int branch);

    public int[] getTotalDistinctsClientsProductMonth(String product);

    /**
     * Query 7: Determina os 3 maiores compradores de cada filial (a nivel de dinheiro faturado)
     * @return Array de Matrizes de strings com o codigo de cliente e total faturado dos 3 maiores compradores para cada filial
     */
    public String[][][] getTop3BuyersByBranch();
}
