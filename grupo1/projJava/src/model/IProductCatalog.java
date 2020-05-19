package model;

public interface IProductCatalog {

    public boolean insertProduct(String productCode);

    public boolean existProduct(String code);

    public int getSize();

}
