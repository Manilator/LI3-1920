package model;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

/**
 * Classe que representa o catalogo de clientes
 */
public class ClientCatalog implements IClientCatalog, Serializable {

    private static final long serialVersionUID = 695838861959300349L;
    private Map<String,IClient> clients;

    /**
     * Contrutor vazio da classe
     */
    public ClientCatalog(){
        clients = new HashMap<>();
    }

    /**
     * Insere o cliente no catalogo de clientes
     * @param clientCode Codigo de cliente
     * @return Devolve o resultado verdadeiro ou falso em relacao a insercao do novo cliente
     */
    public boolean insertClient(String clientCode){

        IClient client = new Client(clientCode);
        if (client.validate()) {
            this.clients.put(clientCode, client);
            return true;
        }
        return false;
    }

    /**
     * Get do numero de clientes
     * @return Devolve um int do numero de clientes
     */
    public int getSize() {
        return this.clients.size();
    }

    /**
     * Verificar se o codigo dado existe
     * @param code Codigo de cliente
     * @return Devolve um boolean que indica se o codigo de cliente existe
     */
    public boolean existClient(String code) {
        return this.clients.containsKey(code);
    }
}
