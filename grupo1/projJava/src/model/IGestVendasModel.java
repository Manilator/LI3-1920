package model;

import java.util.List;

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

    double[][] query4(String product);

    int getReadClients();
  
    String[][] query6(int n);
  
    /**
     * Query 7: Determina os 3 maiores compradores de cada filial (a nivel de dinheiro faturado)
     * @return Array de Matrizes de strings com o codigo de cliente e total faturado dos 3 maiores compradores para cada filial
     */
    public String[][][] query7();

    public String[][] query8(int n);

    public String[][] query9(String product, int n);
}
