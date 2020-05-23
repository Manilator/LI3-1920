package model;

import java.util.HashMap;
import java.util.Map;

import static Utils.Constants.N_MONTHS;

public class RelationWithClient implements IRelationWithClient {

    private Map<String,IInfoClient> infoClients; /**< Códigos de clientes e a sua estrutura atribuída InfoClient */
    private int[] totalProductsSold; /**< Quantidade de produtos que um certo cliente comprou */


    public RelationWithClient() {
        this.infoClients = new HashMap<>();
        this.totalProductsSold = new int[12];
    }

    public void updateRelationWithClient(String client_code, int units, char promotion_type, int month) {
        this.totalProductsSold[month-1] += units;
        if (!this.infoClients.containsKey(client_code)) {
            String _code_client = client_code;

            _code_client = _code_client.replace("\\r\\n", "");
            this.infoClients.put(_code_client, new InfoClient());
        }
        this.infoClients.get(client_code).updateInfoClient(units,promotion_type, month);
    }

    public int[] getTotalProductsSold() {
        return totalProductsSold;
    }

    /**
     * Recolhe o número de clientes distintos que compraram um produto separado por meses
     * @return Array de inteiros separado por meses dos clientes distintos que realizaram compras de um produto especifico
     */
    public int[] getDistinctsClientsProductMonth() {
        int[] totals = new int[N_MONTHS];
        for(IInfoClient e : this.infoClients.values()) {
            boolean[] months = e.didPurchaseMonth();
            for (int i = 0; i < N_MONTHS; i++) {
                if(months[i]) totals[i]++;
            }
        }
        return totals;
    }
}
