package model;

/**
 * Interface da classe que representa uma fatura
 */
public interface IBilling {

    /**
     * Atualiza a classe billing
     * @param totalBilled Quantidade faturada
     * @param unities Numero de unidades compradas
     * @param promotion_type Tipo de promocao utilizada
     * @param branch Filial escolhida
     */
    void updateBilling(double totalBilled, int unities, char promotion_type, int branch);

    /**
     * Get do numero de vendas numa certa filial
     * @param branch Numero da filial
     * @return Devolve o int do numero de vendas numa certa filial
     */
    int getN_sales(int branch);

    /**
     * Get do numero de vendas a preco 0
     * @return Devolve a quantidade de produtos com venda a 0
     */
    int getGiveaways();

    /**
     * Quantidade total faturada
     * @return Devolve um double com a quantidade faturada total
     */
    double getTotalBilled();
}
