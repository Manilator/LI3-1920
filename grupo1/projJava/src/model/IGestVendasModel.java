package model;

import java.io.IOException;
import java.util.List;

public interface IGestVendasModel {


    public int getClientsSize();

    public int getProductsSize();

    public int getReadSales();

    public int getValidSales();

    public int getReadProducts();

    List<String> query1();

    public int getReadClients();

}
