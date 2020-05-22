package model;

import java.util.List;

public interface IGestVendasModel {


    public int getClientsSize();

    public int getProductsSize();

    public int getReadSales();

    public int getValidSales();

    public int getReadProducts();

    List<String> query1();

    public List<Integer> query2(int month);

    public double[][] query4(String product);

    /**
     * Query 7: Determina os 3 maiores compradores de cada filial (a nivel de dinheiro faturado)
     * @return Array de Matrizes de strings com o codigo de cliente e total faturado dos 3 maiores compradores para cada filial
     */
    public String[][][] query7();

    public int getReadClients();

}
