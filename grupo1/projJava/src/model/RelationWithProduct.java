package model;

import java.math.BigDecimal;
import java.util.Arrays;
import java.util.HashMap;

public class RelationWithProduct {

    private HashMap<String,InfoProduct> infoProducts; /**< Códigos de produto e a sua estrutura atribuída InfoProduct */
    private double[] totalBilled; /**< Faturação total por cada mês */

    public RelationWithProduct() {
        this.infoProducts = new HashMap<>();
        this.totalBilled = new double[12];
        Arrays.fill(this.totalBilled, 0);
    }

    public void updateRelationWithProduct(String product_code, int quantity, double billed, int month) {
        this.totalBilled[month-1] += billed;
        if (!this.infoProducts.containsKey(product_code)) {
            String _code_product = product_code;

            _code_product = _code_product.replace("\\r\\n", "");
            this.infoProducts.put(_code_product, new InfoProduct());
        }
        this.infoProducts.get(product_code).updateInfoProduct(quantity,billed,month);
    }

}
