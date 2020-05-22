package model;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class RelationWithProduct implements IRelationWithProduct {

    private Map<String,IInfoProduct> infoProducts; /**< Códigos de produto e a sua estrutura atribuída InfoProduct */
    private double[] totalBilled; /**< Faturação total por cada mês */
    private int[] n_sales;

    public RelationWithProduct() {
        this.infoProducts = new HashMap<>();
        this.totalBilled = new double[12];
        this.n_sales = new int[12];
        Arrays.fill(this.totalBilled, 0);
    }

    public void updateRelationWithProduct(String product_code, int quantity, double billed, int month) {
        this.totalBilled[month-1] += billed;
        this.n_sales[month-1]++;
        if (!this.infoProducts.containsKey(product_code)) {
            String _code_product = product_code;

            _code_product = _code_product.replace("\\r\\n", "");
            this.infoProducts.put(_code_product, new InfoProduct());
        }
        this.infoProducts.get(product_code).updateInfoProduct(quantity,billed,month);
    }

    public double[] getTotalBilled()
    {
        return this.totalBilled;
    }

    /**
     * Devolve a soma do total faturado de todos os meses
     * @return Valor total faturado
     */
    public double getSumTotalBilled()
    {
        return Arrays.stream(this.totalBilled).sum();
    }

    public boolean didPurchaseMonth(int month) {
        return n_sales[month-1] != 0;
    }

}
