package model;

import java.util.List;
import java.util.Map;

/**
 * Interface da classe que representa a faturacao
 */
public interface IBillingCatalog {

    /**
     * Adiciona um BillingProduct dado um codigo de produto
     * @param code Codigo do produto
     */
    void addBillingProduct(String code);

    /**
     * Atualiza a classe Billings
     * @param sale Classe auxiliar de uma venda
     */
    void updateBillings(ISale sale);

    /**
     * N Produtos mais comprados
     * @param n Numero de elementos requisitados
     * @return Devolve uma lista com os produtos mais comprados
     */
    List<String> getTopMostPurchased(int n);

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

    /**
     * Numero total de vendas com faturacao a 0
     * @return Devolve o numero total de vendas com faturacao 0
     */
    int getGiveawaysAmount();

    /**
     * Total faturado em todos os meses
     * @return Devolve a quantidade total faturada
     */
    double getTotalBilledSum();

    /**
     * Numero de produtos comprados
     * @param product Codigo de produto
     * @return Devolve o numero de produtos comprados
     */
    int getProductUnits(String product);

    /**
     * Numero de vendas de uma dada filial num certo mes
     * @param month Mes
     * @param branch Filial
     * @return Devolve o numero de venda da filial no mes escolhido
     */
    int getTotalSalesMonth(int month, int branch);

    /**
     * Numero de vendas de um certo produto
     * @param product Codigo de produto
     * @return Devolve um array com o numero de vendas de um produto por mes
     */
    int[] getNSalesProduct(String product);

    /**
     * Valor faturado nas vendas de um certo produto
     * @param product Codigo de produto
     * @return Devolve um array com a quantidade faturada nas vendas de um produto por mes
     */
    double[] getTotalBilledMonth(String product);
}
