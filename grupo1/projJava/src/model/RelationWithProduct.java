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
        InfoProduct ip = this.infoProducts.get(product_code);
        if (ip == null) {
            String _code_product = product_code;

            _code_product = _code_product.replace("\\r\\n", "");
            this.infoProducts.put(_code_product, new InfoProduct());
            ip = this.infoProducts.get(_code_product);
        }
        ip.updateInfoProduct(quantity,billed,month);
    }

}
