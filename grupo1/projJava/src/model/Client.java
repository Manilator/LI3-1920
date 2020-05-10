package model;

public class Client {

    private final char letter; /**< Primeira letra no código de cliente */
    private final int number; /**< Número presente no código de cliente */

    public Client(char letter, int number) {
        this.letter = letter;
        this.number = number;
    }

    public Client (String clientCode) {
        this.letter = clientCode.charAt(0);
        this.number = Integer.parseInt(clientCode.substring(1));
    }

    public String getClientCode(Client client) {
        return String.format("%c%d",client.getLetter(),client.getNumber());
    }

    public Boolean verifyClient(String clientCode) {
        int number = Integer.parseInt(clientCode.substring(1));
        char letter = clientCode.charAt(0);
        return (number >= 1000 && number <= 5000) &&
                (letter >= 'A' && letter <= 'Z');
    }

    Client newClient(String clientCode) {
        return new Client(clientCode.charAt(0), Integer.parseInt(clientCode.substring(1)));
    }

    public Boolean equalsClient(Client a, Client b) {
        return (a.getLetter() == b.getLetter() && a.getNumber() == b.getNumber());
    }

    public char getLetter() {
        return letter;
    }

    public int getNumber() {
        return number;
    }

    /*
    void destroyClient(Client client) {
        free(client);
    }*/
}
