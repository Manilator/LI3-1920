package model;

/**
 * Interface da classe que representa o catalogo de clientes
 */
public interface IClientCatalog {

    /**
     * Insere o cliente no catalogo de clientes
     * @param clientCode Codigo de cliente
     * @return Devolve o resultado verdadeiro ou falso em relacao a insercao do novo cliente
     */
    boolean insertClient(String clientCode);

    /**
     * Verificar se o codigo dado existe
     * @param code Codigo de cliente
     * @return Devolve um boolean que indica se o codigo de cliente existe
     */
    boolean existClient(String code);

    /**
     * Get do numero de clientes
     * @return Devolve um int do numero de clientes
     */
    int getSize();

}
