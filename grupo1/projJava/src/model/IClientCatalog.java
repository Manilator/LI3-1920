package model;

public interface IClientCatalog {

    public boolean insertClient(String clientCode);

    public boolean existClient(String code);

    public int getSize();

}
