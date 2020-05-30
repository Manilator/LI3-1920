package model;

public interface IClientCatalog {

    boolean insertClient(String clientCode);

    boolean existClient(String code);

    int getSize();

}
