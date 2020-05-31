package model;

import java.io.Serializable;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import static Utils.Constants.N_MONTHS;

/**
 * Classe que contem o modelo de relacao de um produto e os varios clientes que o compraram
 */
public class RelationWithClient implements IRelationWithClient, Serializable {

    private static final long serialVersionUID = 6685298803648026223L;
    private Map<String,IInfoClient> infoClients;
    private int[] totalProductsBought;

    /**
     * Construtor vazio da classe
     */
    public RelationWithClient() {
        this.infoClients = new HashMap<>();
        this.totalProductsBought = new int[12];
    }

    /**
     * Função que atualiza a estrutura RelationWithClient com as informações dadas (!!!) confirmar pls
     * @param client_code código do cliente
     * @param units unidades compradas pelo cliente a ser somada à estrutura
     * @param promotion_type tipo de promoção da compra
     * @param month mês que vai determinar a posição onde as informações serão somadas à estrutura
     * @param totalbilled montante faturado com a compra do produto a ser somada ao total faturado
     */
    public void updateRelationWithClient(String client_code, int units, char promotion_type, int month, double totalbilled) {
        this.totalProductsBought[month-1] += units;
        if (!this.infoClients.containsKey(client_code)) {
            String _code_client = client_code;

            _code_client = _code_client.replace("\\r\\n", "");
            this.infoClients.put(_code_client, new InfoClient());
        }
        this.infoClients.get(client_code).updateInfoClient(units,promotion_type, month, totalbilled);
    }

    /**
     * Get da variável que contém a quantidade de produtos que um certo cliente comprou
     * @return Array de ints com a quantidade de produtos que um certo cliente comprou
     */
    public int[] getTotalProductsBought() {
        return totalProductsBought.clone();
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

    /**
     * Recolhe todos os clientes que compraram o produto
     * @return Set com todas as entradas do Hashmap que contém os clientes que compraram o produto
     */
    public Set<Map.Entry<String, IInfoClient>> getAllClients() {
        return new HashSet<>(this.infoClients.entrySet());
    }
}
