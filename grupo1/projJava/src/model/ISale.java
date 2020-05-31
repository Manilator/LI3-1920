package model;

/**
 * Interface da classe auxiliar Sale
 */
public interface ISale {

    /**
     * Get product
     * @return Devolve o código do produto
     */
    String getProduct();

    /**
     * Get client
     * @return Devolve o código do cliente
     */
    String getClient();

    /**
     * Get price
     * @return Devolve o preço
     */
    double getPrice();

    /**
     * Get units
     * @return Devolve o número de unidades vendidas
     */
    int getUnits();

    /**
     * Get promotion
     * @return Devolve o tipo de promoção
     */
    char getPromotion();

    /**
     * Get month
     * @return Devolve o mês
     */
    int getMonth();

    /**
     * Get branch
     * @return Devolve o número da filial
     */
    int getBranch();

}