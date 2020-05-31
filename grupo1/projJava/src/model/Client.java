package model;

import java.io.Serializable;
import java.util.regex.Matcher;

import static Utils.Constants.clientPattern;

/**
 * Classe que representa o modelo cliente
 */
public class Client implements IClient, Serializable {

    private static final long serialVersionUID = 8176186024578778414L;
    private final char letter;
    private final int number;

    /**
     * Construtor com parametros da classe
     * @param clientCode Codigo do cliente
     */
    public Client (String clientCode) {
        this.letter = clientCode.charAt(0);
        this.number = Integer.parseInt(clientCode.substring(1));
    }

    /**
     * Valida um cliente
     * @return True se o código for valido, False caso contrario
     */
    public boolean validate() {
        String id = this.letter +
                String.valueOf(this.number);
        Matcher e = clientPattern.matcher(id);
        return e.matches();
    }

}
