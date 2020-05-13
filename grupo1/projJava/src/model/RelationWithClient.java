package model;

import java.util.Hashtable;

public class RelationWithClient {

    private Hashtable<String,InfoClient> infoClients; /**< Códigos de clientes e a sua estrutura atribuída InfoClient */
    private int totalProductsSold; /**< Quantidade de produtos que um certo cliente comprou */


    public RelationWithClient() {
        this.infoClients = new Hashtable<>();
        this.totalProductsSold = 0;
    }

    public void updateRelationWithClient(String client_code, int units, char promotion_type) {
        this.totalProductsSold += units;
        InfoClient ic = this.infoClients.get(client_code);
        if (ic == null) {
            String _code_client = client_code;

            _code_client = _code_client.replace("\\r\\n", "");
            this.infoClients.put(_code_client, new InfoClient());
            ic = this.infoClients.get(_code_client);
        }
        ic.updateInfoClient(units,promotion_type);
    }
}
