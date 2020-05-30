package model;

public interface ISale {

    /**
     * Get product
     * @return Devolve o código do produto
     */
    public String getProduct();

    /**
     * Get client
     * @return Devolve o código do cliente
     */
    public String getClient();

    /**
     * Get price
     * @return Devolve o preço
     */
    public double getPrice();

    /**
     * Get units
     * @return Devolve o número de unidades vendidas
     */
    public int getUnits();

    /**
     * Get promotion
     * @return Devolve o tipo de promoção
     */
    public char getPromotion();

    /**
     * Get month
     * @return Devolve o mês
     */
    public int getMonth();

    /**
     * Get branch
     * @return Devolve o número da filial
     */
    public int getBranch();

}