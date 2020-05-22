package model;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import static Utils.Constants.N_MONTHS;

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

    public boolean didPurchaseMonth(int month) {
        return n_sales[month-1] != 0;
    }

    /**
     * Get amount of distinct products that bought in each month
     * @return Array of ints with amount of distinct products bought
     */
    public int[] getAmountDistinctInfoProducts(){
        int[] result = new int[N_MONTHS];
        int[] tmp;
        for (String productCode: infoProducts.keySet()){
            tmp = infoProducts.get(productCode).getQuantities();
            for (int i=0;i<N_MONTHS;i++)
                if(tmp[i] != 0)
                    result[i] += 1;
        }

        return result;
    }

    /**
     * Get amount the amount billed each month
     * @return Array of ints with the amount billed each month
     */
    public double[] getTotalBilled() {
        return totalBilled;
    }

    /**
     * Get amount of sales made at each month
     * @return Array of ints with the amount of sales in each month
     */
    public int[] getN_sales() {
        return n_sales;
    }

    /**
     * Get amount of sales made at each month
     * @return Array of ints with the amount of sales in each month
     */
    public Set<String> getTotalDistinctProducts() {
        return this.infoProducts.keySet();
    }
}
