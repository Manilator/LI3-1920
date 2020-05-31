package model;

/**
 * Interface da classe que representa a faturacao que um produto teve
 */
public interface IBillingProduct {

    /**
     * Atualiza a classe BillingProdutct
     * @param totalBilled Faturacao dada
     * @param unities Numero de unidades
     * @param promotion_type Tipo de promocao
     * @param branch Numero de filial
     * @param month Numero do mes
     */
    void updateBillingProduct(double totalBilled, int unities, char promotion_type, int branch, int month);

    /**
     * Numero de vendas em cada mes
     * @return Devolve o numero venda em cada mes
     */
    int[] getN_sales();

    /**
     * A faturacao total em cada mes
     * @return Devolve faturacao total em cada mes
     */
    double[] getTotalBilled();

    /**
     * Numero total de unidades
     * @return Devolve o numero total de unidades
     */
    int getTotalUnits();

    /**
     * Faturação dividida por mes e filial
     * @return Devolve o clone da variavel
     */
    double[][] getBranchesBilled();
}
