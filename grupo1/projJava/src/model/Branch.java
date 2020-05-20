package model;

import java.util.HashMap;
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

    public int distinctClientsMonth(int month) {
        HashMap<String, IRelationWithProduct> list = new HashMap<>(this.clientsProducts);
        return (int) this.clientsProducts.values().stream().filter(e -> e.didPurchaseMonth(month)).count();
    }

    public int[] getDistinctsClientsProductMonth(String product) {
        return this.productsClients.get(product).getDistinctsClientsProductMonth();
    }
}
