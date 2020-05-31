package model;

import java.util.Map;
import java.util.Set;

/**
 * Interface da classe que contem o modelo de relacao de um produto e os varios clientes que o compraram
 */
public interface IRelationWithClient {

    /**
     * Função que atualiza a estrutura RelationWithClient com as informações dadas (!!!) confirmar pls
     * @param client_code código do cliente
     * @param units unidades compradas pelo cliente a ser somada à estrutura
     * @param promotion_type tipo de promoção da compra
     * @param month mês que vai determinar a posição onde as informações serão somadas à estrutura
     * @param totalbilled montante faturado com a compra do produto a ser somada ao total faturado
     */
    void updateRelationWithClient(String client_code, int units, char promotion_type, int month, double totalbilled);

    /**
     * Get da variável que contém a quantidade de produtos que um certo cliente comprou
     * @return Array de ints com a quantidade de produtos que um certo cliente comprou
     */
    int[] getTotalProductsBought();

    /**
     * Recolhe o número de clientes distintos que compraram um produto separado por meses
     * @return Array de inteiros separado por meses dos clientes distintos que realizaram compras de um produto especifico
     */
    int[] getDistinctsClientsProductMonth();

    /**
     * Recolhe todos os clientes que compraram o produto
     * @return Set com todas as entradas do Hashmap que contém os clientes que compraram o produto
     */
    Set<Map.Entry<String, IInfoClient>> getAllClients();
}
