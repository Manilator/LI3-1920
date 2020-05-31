package model;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

import static Utils.Constants.N_MONTHS;

/**
 * Classe que representa uma filial
 */
public class Branch implements IBranch, Serializable {

    private static final long serialVersionUID = -7476925717995734343L;
    private Map<String, IRelationWithClient> productsClients;
    private Map<String, IRelationWithProduct> clientsProducts;

    /**
     * Construtor vazio da classe
     */
    public Branch() {
        this.productsClients = new HashMap<>();
        this.clientsProducts = new HashMap<>();
    }

    /**
     * Atualiza a classe
     * @param client_code Codigo do cliente
     * @param product_code Codigo de produto
     * @param units Numero de unidades compradas
     * @param promotion_type Tipo de promocao
     * @param billed Quantidade faturada
     * @param month Mes da compra
     */
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
        this.productsClients.get(product_code).updateRelationWithClient(client_code, units, promotion_type, month, billed);
        this.clientsProducts.get(client_code).updateRelationWithProduct(product_code, units, billed, month);
    }

    /**
     * Hashtable com os códigos de todos os produtos que efetuaram compras na filial
     * @param productsBought Map com códigos de produtos como valores e chaves que compraram na filial
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
     * @param clientCode Código de cliente
     * @param shopLog Array de doubles com numero de compras, produtos distintos e valor total gasto, em cada mês na filial
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
     * Dado um código de cliente retorna uma hashtable com os códigos de produtos mais comprados pelo mesmo na filial
     * @param clientCode String com o código do cliente
     * @param productsBought Hashtable com os códigos de produtos mais comprados pelo mesmo em todas as filiais
     * @return Hashtable com os códigos de produtos mais comprados pelo mesmo na filial
     */
    public Map<String,Integer> getClientsFavoriteProductsBranch(String clientCode, Map<String,Integer> productsBought){
        return clientsProducts.get(clientCode).getClientsFavoriteProductsBranch(productsBought);
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
        int[] result = new int[12];
        try {
            result = this.productsClients.get(product).getDistinctsClientsProductMonth();
        } catch (Exception e) {
            Arrays.fill(result,0);
        }
        return result;
    }

    /**
     * Determina numa dada filial os 3 maiores compradores (a nivel de dinheiro faturado)
     * @return Matriz de strings com o codigo de cliente e total faturado dos 3 maiores compradores dessa filial
     */
    public String[][] getTop3BuyersInBranchX() {

        // para cada cliente no clientsProducts ha o valor total faturado:
        Map<String, Double> totais = this.clientsProducts.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e -> e.getValue().getSumTotalBilled()));

        List<Map.Entry<String, Double>> clients = new ArrayList<>(totais.entrySet());

        // ordenar a lista de ordem decrescente por valor
        final double aux[] = new double[1];
        Comparator<Map.Entry<String, Double>> comp = (a, b) ->
                (int) ((aux[0] = b.getValue() - a.getValue())
                                        == 0 ? a.getKey().compareTo(b.getKey()) : aux[0]);
        clients.sort(comp);

        // devolver os 3 maiores
        String[][] result = new String[3][2];
        int i = 0;
        for( Map.Entry<String, Double> c : clients ) {
            if (i >= 3) {
                break;
            }
            result[i][0] = c.getKey();
            result[i++][1] = String.valueOf(c.getValue());
        }
        return result;
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

    /**
     * Função que recolhe a lista de clientes e associado a eles um set de códigos de produtos que comprou
     * @return Map com códigos de clientes e associados a eles um Set de códigos de produtos
     */
    public Map<String, Set<String>> getClientsDistinctProducts() { 
        return this.clientsProducts
                        .entrySet()
                        .stream()
                        .collect(Collectors
                                .toMap(Map.Entry::getKey, 
                                        e -> e.getValue().getTotalDistinctProducts()));
    }

    /**
     * Recolhe todos os clientes que compraram o produto
     * @param product Código do produto
     * @return Set com todas as entradas do Hashmap que contém os clientes que compraram o produto
     */
    public Set<Map.Entry<String, IInfoClient>> getProductAllClients(String product) {
        return this.productsClients.get(product).getAllClients();
    }

    /**
     * Calcula o numero total de compras por mês de uma dada filial e devolve os resultados
     * @param branch Número da filial
     * @return Devolve um array de inteiros com as compras feitas numa dada filial nos 12 meses do ano
     * @throws Exception Caso alguma informação esteja corrompida este devolve o erro
     */
    public int[] getBranchShoppingFrequency(int branch) throws Exception{
        int[] result = new int[N_MONTHS];
        for (String key : this.productsClients.keySet()){
            int month = 0;
            for (int monthBuys : this.productsClients.get(key).getTotalProductsBought())
                result[month++] += monthBuys;
        }
        return result;
    }

    /**
     * A quantidade de clientes distintos que compraram num certo mês numa certa filial
     * @param branch Número da filial
     * @return Devolve um array de ints com o numero de clientes distintos que compraram num certo mês dividido por filial
     */
    public int[] getBranchNumberOfDistinctClients(int branch){
        int[] result = new int[N_MONTHS];
        for (String key : this.productsClients.keySet()){
            int month = 0;
            for (int monthSales : this.productsClients.get(key).getTotalProductsBought()){
                if(monthSales > 0)
                    result[month] += 1;
                month++;
            }
        }
        return result;
    }

    /**
     * Clientes que nunca compraram
     * @return Devolve um Set com os clientes que nunca fizeram compras
     */
    public Set<String> getClientWhoBought(){
        return this.clientsProducts.keySet();
    }
}
