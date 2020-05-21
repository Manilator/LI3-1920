package model;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Branch implements IBranch {

    private Map<String, IRelationWithClient> productsClients; /**< Códigos de produtos e a sua estrutura atribuída RelationWithClient */
    private Map<String, IRelationWithProduct> clientsProducts; /**< Códigos de clientes e a sua estrutura atribuída RelationWithProduct */

    public Branch() {
        this.productsClients = new HashMap<>();
        this.clientsProducts = new HashMap<>();
    }

    public void addRelationWithClient(String product_code, RelationWithClient rcc) {
        this.productsClients.put(product_code,rcc);
    }

    public void addRelationWithProduct(String client_code, RelationWithProduct rcp) {
        this.clientsProducts.put(client_code, rcp);
    }

    private IRelationWithClient getRelationWithClient(String cod) {
        return this.productsClients.get(cod);
    }

    private IRelationWithProduct getRelationWithProduct(String cod) {
        return this.clientsProducts.get(cod);
    }

    public void updateBranch(String client_code, String product_code, int units, char promotion_type, double billed, int month) {
        if (!this.productsClients.containsKey(product_code)) {
            String _code_product = product_code;

            _code_product = _code_product.replace("\\r\\n", "");
            this.productsClients.put(_code_product, new RelationWithClient());
        }
        if (!this.clientsProducts.containsKey(client_code)) {
            String _code_client = client_code;

            _code_client = _code_client.replace("\\r\\n", "");
            this.clientsProducts.put(_code_client, new RelationWithProduct());
        }
        this.productsClients.get(product_code).updateRelationWithClient(client_code, units, promotion_type, month);
        this.clientsProducts.get(client_code).updateRelationWithProduct(product_code, units, billed, month);
    }

    /**
     * Hashtable com os códigos de todos os produtos que efetuaram compras na filial
     * @return Map com códigos de produtos como valores e chaves que compraram na filial
     */
    public Map<String, String> getProductsBought(Map<String, String> productsBought){
        for (String productCode : this.productsClients.keySet())
            if (!productsBought.containsKey(productCode))
                productsBought.put(productCode,productCode);
        return productsBought;
    }

    /**
     * Dado um código de cliente, determinar, para cada mês na filial, quantas compras fez, quantos produtos distintos comprou e quanto gastou no total
     * @return Array de doubles com numero de compras, produtos distintos e valor total gasto, em cada mês na filial
     */
    public double[][] getClientShoppingLog(String clientCode, double[][] shopLog){
        int[] distinctProducts = clientsProducts.get(clientCode).getAmountDistinctInfoProducts();
        double[] spentTotal = clientsProducts.get(clientCode).getTotalBilled();
        int[] numberSales = clientsProducts.get(clientCode).getN_sales();

        for (int i=0; i<12 ; i++){
            shopLog[i][0] += numberSales[i];
            shopLog[i][1] += distinctProducts[i];
            shopLog[i][2] += spentTotal[i];
        }

        return shopLog;
    }

    /**
     * Função que recolhe o número de clientes que realizaram compras num mês dado
     * @param month mês no qual os clientes realizaram compras
     * @return número de clientes distintos que realizaram compras num mês especifico
     */
    public int distinctClientsMonth(int month) {
        return (int) this.clientsProducts.values().stream().filter(e -> e.didPurchaseMonth(month)).count();
    }

    /**
     * Função que recolhe o número de clientes distintos que realizaram compras separado por meses
     * @param product produto que se pretende obter o número de clientes distintos que o compraram
     * @return Array de inteiros que correspondem ao número de clientes distintos que compraram certo produto separado por meses
     */
    public int[] getDistinctsClientsProductMonth(String product) {
        return this.productsClients.get(product).getDistinctsClientsProductMonth();
    }

    /**
     * Função que recolhe a lista de clientes que realizaram compras num certo mês
     * @param month mês no qual os clientes realizaram compras
     * @return Lista de códigos de clientes que realizaram compras no mês
     */
    public List<String> getClientsWithPurchasesMonth(int month) {
        List<String> list = new ArrayList<>();
        for (Map.Entry<String, IRelationWithProduct> c : this.clientsProducts.entrySet()) {
            if(c.getValue().didPurchaseMonth(month))
                list.add(c.getKey());
        }
        return list;
    }
}
