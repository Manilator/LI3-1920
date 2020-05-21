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
     * @return Array de doubles com numero de compras, produtos distintos e valor total gasto, em cada mês
     */
    double[][] getClientShoppingLog();

    double[][] query4(String product);

    int getReadClients();

}
