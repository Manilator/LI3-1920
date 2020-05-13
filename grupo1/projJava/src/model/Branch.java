package model;

import javax.management.relation.Relation;
import java.util.Hashtable;

public class Branch {

    private Hashtable<String, RelationWithClient> productsClients; /**< Códigos de produtos e a sua estrutura atribuída RelationWithClient */
    private Hashtable<String, RelationWithProduct> clientsProducts; /**< Códigos de clientes e a sua estrutura atribuída RelationWithProduct */

    public Branch() {
        this.productsClients = new Hashtable<>();
        this.clientsProducts = new Hashtable<>();
    }

    public void addRelationWithClient(String product_code, RelationWithClient rcc) {
        this.productsClients.put(product_code,rcc);
    }

    public void addRelationWithProduct(String client_code, RelationWithProduct rcp) {
        this.clientsProducts.put(client_code, rcp);
    }

    private RelationWithClient getRelationWithClient(String cod) {
        return this.productsClients.get(cod);
    }

    private RelationWithProduct getRelationWithProduct(String cod) {
        return this.clientsProducts.get(cod);
    }

    public void updateBranch(String client_code, String product_code, int units, char promotion_type, double billed, int month) {
        RelationWithClient rcc = this.productsClients.get(product_code);
        RelationWithProduct rcp = this.clientsProducts.get(client_code);
        if (rcc == null) {
            String _code_product = product_code;

            _code_product = _code_product.replace("\\r\\n", "");
            this.productsClients.put(_code_product, new RelationWithClient());
            rcc = this.productsClients.get(_code_product);
        }
        if (rcp == null) {
            String _code_client = client_code;

            _code_client = _code_client.replace("\\r\\n", "");
            this.clientsProducts.put(_code_client, new RelationWithProduct());
            rcp = this.clientsProducts.get(_code_client);
        }
        rcc.updateRelationWithClient(client_code, units, promotion_type);
        rcp.updateRelationWithProduct(product_code, units, billed, month);
    }

}
