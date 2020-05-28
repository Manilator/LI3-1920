package model;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import static Utils.Constants.N_MONTHS;

public class RelationWithProduct implements IRelationWithProduct {

    private Map<String,IInfoProduct> infoProducts; /**< Códigos de produto e a sua estrutura atribuída InfoProduct */
    private double[] totalBilled; /**< Faturação total por cada mês */
    private int[] n_sales; /**< Numero de compras por cada mês */

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

    /**
     * Devolve o numero de produtos distintos comprados em cada mês
     * @return Array de ints com a quantidade de produtos distintos comprados em cada mês
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
     * Deolve o total faturado em cada mês
     * @return Array de ints com o total faturado em cada mês
     */
    public double[] getTotalBilled() {
        return totalBilled.clone();
    }

    /**
     * Devolve a quantidade de vendas feitas em cada mês
     * @return Array de ints com a quantidade de vendas feitas em cada mês
     */
    public int[] getN_sales() {
        return n_sales.clone();
    }

    /**
     * Dada uma hashtable com os códigos de produtos atualizar com as quantidades compradas por cada
     * @param productsBought Hashtable com os códigos de produtos mais comprados pelo mesmo em todas as filiais
     * @return Hashtable com os códigos de produtos mais comprados pelo mesmo na filial
     */
    public Map<String,Integer> getClientsFavoriteProductsBranch(Map<String,Integer> productsBought){
        for (String key : infoProducts.keySet()){
            if(productsBought.containsKey(key))
                productsBought.put(key, productsBought.get(key) + infoProducts.get(key).getTotalQuantity());
            else
                productsBought.put(key, infoProducts.get(key).getTotalQuantity());
        }
        return productsBought;
    }
  
    /**
     * Get amount of sales made at each month
     * @return Array of ints with the amount of sales in each month
     */
    public Set<String> getTotalDistinctProducts() {
        return this.infoProducts.keySet();
    }
}
