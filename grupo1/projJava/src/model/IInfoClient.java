package model;

/**
 * Interface da classe que contem a informacao de um dado cliente
 */
public interface IInfoClient {

    /**
     * Função que atualiza a estrutura InfoClient com as informações dadas (!!!) confirmar pls
     * @param units unidades compradas pelo cliente a ser somada à estrutura
     * @param promotion_type tipo de promoção da compra
     * @param month mês que vai determinar a posição onde as informações serão somadas à estrutura
     * @param totalBilled montante faturado com a compra do produto a ser somada ao total faturado
     */
    void updateInfoClient(int units, char promotion_type, int month, double totalBilled);

    /**
     * Recolhe se um cliente realizou a compra de um produto por mês
     * @return Array de booleanos em que cada entrada corresponde aos meses
     */
    boolean[] didPurchaseMonth();

    /**
     * Calcula o total gasto
     * @return Total gasto
     */
    double getTotalBilled();

    /**
     * Calcula o total de unidades
     * @return Total de unidades
     */
    int getTotalUnits();
}
