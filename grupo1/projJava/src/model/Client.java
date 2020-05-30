package model;

import java.io.Serializable;
import java.util.regex.Matcher;

import static Utils.Constants.clientPattern;

public class Client implements IClient, Serializable {

    private static final long serialVersionUID = 8176186024578778414L;
    private final char letter; /**< Primeira letra no código de cliente */
    private final int number; /**< Número presente no código de cliente */

    public Client (String clientCode) {
        this.letter = clientCode.charAt(0);
        this.number = Integer.parseInt(clientCode.substring(1));
    }

    public boolean validate() {
        String id = this.letter +
                String.valueOf(this.number);
        Matcher e = clientPattern.matcher(id);
        return e.matches();
    }

}
