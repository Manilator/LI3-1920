package model;

import java.util.HashMap;
import java.util.Map;

public class RelationWithClient implements IRelationWithClient {

    private Map<String,IInfoClient> infoClients; /**< Códigos de clientes e a sua estrutura atribuída InfoClient */
    private int totalProductsSold; /**< Quantidade de produtos que um certo cliente comprou */


    public RelationWithClient() {
        this.infoClients = new HashMap<>();
        this.totalProductsSold = 0;
    }

    public void updateRelationWithClient(String client_code, int units, char promotion_type) {
        this.totalProductsSold += units;
        if (!this.infoClients.containsKey(client_code)) {
            String _code_client = client_code;

            _code_client = _code_client.replace("\\r\\n", "");
            this.infoClients.put(_code_client, new InfoClient());
        }
        this.infoClients.get(client_code).updateInfoClient(units,promotion_type);
    }

    public int getTotalProductsSold() {
        return totalProductsSold;
    }
}
