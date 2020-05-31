package model;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

public class ClientCatalog implements IClientCatalog, Serializable {

    private static final long serialVersionUID = 695838861959300349L;
    private Map<String,IClient> clients;

    public ClientCatalog(){
        clients = new HashMap<>();
    }

    /**
     * (!!!)
     * @param clientCode (!!!)
     * @return (!!!)
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
     * (!!!)
     * @return (!!!)
     */
    public int getSize() {
        return this.clients.size();
    }

    /**
     * (!!!)
     * @param code (!!!)
     * @return (!!!)
     */
    public boolean existClient(String code) {
        return this.clients.containsKey(code);
    }
}
