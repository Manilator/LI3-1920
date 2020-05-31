package controller;

import java.io.IOException;

/**
 * Interface da classe que controla o fluxo do programa
 */
public interface IGestVendasController {

    /**
     * Função que inicia o controller
     * @throws IOException Exceção se ocorrer erros ao ler os ficheiros
     */
    void startController() throws IOException, ClassNotFoundException;

}
