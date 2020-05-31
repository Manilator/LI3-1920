package model;

/**
 * Interface da classe que representa o modelo cliente
 */
public interface IClient {

    /**
     * Valida um cliente
     * @return True se o código for valido, False caso contrario
     */
    boolean validate();

}
