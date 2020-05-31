package model;

/**
 * Interface da classe que contem a informacao de um dado produto
 */
public interface IInfoProduct {

    /**
     * Função que atualiza a estrutura InfoProduct com as informações dadas (!!!) confirmar pls
     * @param quantity quantidade comprada do produto a ser somada à estrutura
     * @param billed montante faturado com a compra do produto a ser somada à estrutura
     * @param month mês que vai determinar a posição onde as informações serão somadas à estrutura
     */
    void updateInfoProduct(int quantity, double billed, int month);

    /**
     * Get amount of products bought each month
     * @return Array of ints with the amount of products bought
     */
    int[] getQuantities();

    /**
     * Devolve a quantidade de compras do produto no ano inteiro
     * @return Int com a quantidade comprada do produto no ano inteiro
     */
    int getTotalQuantity();
}
