package model;

import java.util.List;
import java.util.Map;

public interface IGestVendasModel {


    int getClientsSize();

    int getProductsSize();

    int getReadSales();

    int getValidSales();

    int getReadProducts();

    /**
     * Lista ordenada alfabeticamente com os códigos dos produtos nunca comprados e o seu respetivo total
     * @return Lista ordenada com os códigos de produtos nunca comprados
     */
    List<String> getProductNeverBought();

    List<Integer> query2(int month);

    /**
     * Dado um código de cliente, determinar, para cada mês, quantas compras fez, quantos produtos distintos comprou e quanto gastou no total
     * @param clientCode Code of the selected client
     * @return Array de doubles com numero de compras, produtos distintos e valor total gasto, em cada mês
     */
    double[][] getClientShoppingLog(String clientCode);

    /**
     * Dado um código de cliente retorna uma lista ordenada com os códigos de produtos mais comprados pelo mesmo
     * @param clientCode String com o código do cliente
     * @return Lista de strings com códigos de produtos mais comprados
     */
    String[][] getClientsFavoriteProducts(String clientCode);

    double[][] query4(String product);

    int getReadClients();
  
    String[][] query6(int n);
  
    /**
     * Query 7: Determina os 3 maiores compradores de cada filial (a nivel de dinheiro faturado)
     * @return Array de Matrizes de strings com o codigo de cliente e total faturado dos 3 maiores compradores para cada filial
     */
    String[][][] query7();

    String[][] query8(int n);

    String[][] query9(String product, int n);

    /**
     * Query 10: Determina mes a mes, e para cada mes, filial a filial, a faturacao total com cada produto
     * @return HashMap com codigos de produto e correspondente matriz de faturacao (por meses e por filiais)
     */
    Map<String, double[][]> query10();

    /**
     * Devolve o numero total de compras por mês, faturação total por mês por filial e global, numero de clientes distintos a comprar cada mes por filial
     * @return HashMap com codigos de produto e correspondente matriz de faturacao (por meses e por filiais)
     */
    void ce2();
}
