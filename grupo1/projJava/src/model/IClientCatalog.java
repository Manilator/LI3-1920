package model;

public interface IClientCatalog {

    /**
     * (!!!)
     * @param clientCode (!!!)
     * @return (!!!)
     */
    boolean insertClient(String clientCode);

    /**
     * (!!!)
     * @param code (!!!)
     * @return (!!!)
     */
    boolean existClient(String code);

    /**
     * (!!!)
     * @return (!!!)
     */
    int getSize();

}
