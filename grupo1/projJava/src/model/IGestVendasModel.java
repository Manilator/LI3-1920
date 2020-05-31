package model;

import java.io.IOException;

import java.util.List;
import java.util.Map;

/**
 * Interface da classe que contem a estrutura modular do sistema
 */
public interface IGestVendasModel {

    /**
     * Leitura e parsing do ficheiro dos clientes
     * @param clientPath Caminho para o ficheiro dos clientes
     */
    void parseClients(String clientPath);

    /**
     * Leitura e parsing do ficheiro dos produtos
     * @param productPath Caminho para o ficheiro dos produtos
     */
    void parseProducts(String productPath);

    /**
     * Leitura e parsing do ficheiro das vendas
     * @param salesPath Caminho para o ficheiro das vendas
     */
    void parseSales(String salesPath);

    /**
     * Numero de clientes na estrutura
     * @return Devolve o numero de clientes na estrutura
     */
    int getClientsSize();

    /**
     * Numero de produtos na estrutura
     * @return Devolve o numero de produtos na estrutura
     */
    int getProductsSize();

    /**
     * Numero de vendas lidas
     * @return Devolve o numero de vendas lidas
     */
    int getReadSales();

    /**
     * Numero de vendas validas
     * @return Devolve o numero de vendas validas
     */
    int getValidSales();

    /**
     * Numero de produtos lidos
     * @return Devolve o numero de produtos lidos
     */
    int getReadProducts();

    /**
     * Numero de clientes lidos
     * @return Devolve o numero de clientes lidos
     */
    int getReadClients();

    /**
     * Lista ordenada alfabeticamente com os códigos dos produtos nunca comprados e o seu respetivo total
     * @return Lista ordenada com os códigos de produtos nunca comprados
     */
    List<String> getProductNeverBought();

    /**
     * Dado um mês determinar o número total global de vendas realizadas e o número total
     * de clientes distintos que as fizeram para cada uma das filiais
     * @param month Mês
     * @return Lista de inteiros com os valores requisitados
     */
    List<Integer> totalSalesCountAndDistinctBuyers(int month);

    /**
     * Dado um código de cliente, determinar, para cada mês, quantas compras fez, quantos produtos distintos comprou e quanto gastou no total
     * @param clientCode Code of the selected client
     * @return Array de doubles com numero de compras, produtos distintos e valor total gasto, em cada mês
     */
    double[][] getClientShoppingLog(String clientCode);

    /**
     * Dado um código de cliente retorna uma lista ordenada com os códigos de produtos mais comprados pelo mesmo
     * @param clientCode String com o código do cliente
     * @return Lista de strings com códigos de produtos mais comprados
     */
    String[][] getClientsFavoriteProducts(String clientCode);

    /**
     * Dado o código de um produto existente, determinar, mês a mês, quantas vezes foi comprado, por quantos clientes diferentes e o total faturado
     * @param product Código de produto
     * @return Devolve uma matriz com a quantidade de vezes que foi comprado, por mes e filial
     */
    double[][] productInfoByMonth(String product);

    /**
     * Determinar os N produtos mais comprados
     * @param n Número de elementos a mostrar
     * @return Devolve uma matriz com Strings com o codigo de cliente e o numero de produtos diferentes comprados
     */
    String[][] topMostBoughtProducts(int n);
  
    /**
     * Determina os 3 maiores compradores de cada filial (a nivel de dinheiro faturado)
     * @return Array de Matrizes de strings com o codigo de cliente e total faturado dos 3 maiores compradores para cada filial
     */
    String[][][] top3BuyersByBranch();

    /**
     * Determinar os top N clientes que compraram produtos únicos
     * @param n Número de elementos a mostrar
     * @return Devolve uma matriz com Strings com o codigo de cliente e o numero de produtos diferentes comprados
     */
    String[][] topClientsWhoBoughtDistinctProducts(int n);

    /**
     * Dado um codigo de produto determinar o conjunto dos X clientes que mais o compraram e qual o valor gasto por cada
     * @param product Código de produto
     * @param n Número de elementos a mostrar
     * @return Devolve uma matriz de Strings com codigo de cliente e o valor gasto por ele
     */
    String[][] topNBuyersAndMoneySpent(String product, int n);

    /**
     * Determina mes a mes, e para cada mes, filial a filial, a faturacao total com cada produto
     * @return HashMap com codigos de produto e correspondente matriz de faturacao (por meses e por filiais)
     */
    Map<String, double[][]> totalBillingByMonthAndBranch();

    /**
     * Numero de clientes distintos a comprar cada mes por filial
     * @return Devolve um array multi dimensional de ints com o numero de clientes distintos que compraram num certo mês dividido por filial
     */
    int[][] getNumberOfDistinctClients();

    /**
     * Devolve o numero total de compras por mês
     * @return Devolve um array de inteiros com as compras feitas nos 12 meses do ano
     */
    int[] getShoppingFrequency();

    /**
     * Faturação total por mês por filial e global
     * @return Devolve um array multi dimensional de doubles com a faturacao por mes e filial
     */
    double[][] getBillingByMonthAndBranch();

    /**
     * Guarda o estado atual do Model para um dado ficheiro
     * @param path Caminho do ficheiro a guardar
     * @throws IOException Exceção de erro a escrever para o ficheiro
     */
    void save(String path) throws IOException;

    /**
     * Apresenta ao utilizador os dados referentes ao último ficheiro de vendas lido,
     * designadamente, nome do ficheiro, número total de registos de venda errados,
     * número total de produtos, total de diferentes produtos comprados, total de não
     * comprados, número total de clientes e total dos que realizaram compras, total de
     * clientes que nada compraram, total de compras de valor total igual a 0.0 e faturação
     * total.
     * @return String array com o mencionado acima
     */
    String[] statisticalConsult();

}
