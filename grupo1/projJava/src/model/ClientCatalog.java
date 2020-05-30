package model;

import java.util.HashMap;
import java.util.Map;

public class ClientCatalog implements IClientCatalog {

    private final Map<String,IClient> clients;

    public ClientCatalog(){
        clients = new HashMap<>();
    }

    public boolean insertClient(String clientCode){

        IClient client = new Client(clientCode);
        if (client.validate()) {
            this.clients.put(clientCode, client);
            return true;
        }
        return false;
    }

    public int getSize() {
        return this.clients.size();
    }

    public boolean existClient(String code) {
        return this.clients.containsKey(code);
    }
}
