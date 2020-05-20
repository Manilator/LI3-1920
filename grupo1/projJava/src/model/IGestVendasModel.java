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

    public String[][] query6(int n);

    public int getReadClients();

}
