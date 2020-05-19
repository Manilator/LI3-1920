package model;

import java.io.IOException;

public interface IGestVendasModel {

    public void startSGV() throws IOException;

    public int getClientsSize();

    public int getProductsSize();

    public int getReadSales();

    public int getValidSales();

    public int getReadProducts();

}
