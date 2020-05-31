package view;

/**
 * Interface da classe que representa as tabelas da view
 */
public interface ITable {

    /**
     * Função responsável por mostrar o resultado da query 3 ao utilizador em forma de tabela por meses e totais
     * @param list Lista com os dados a mostrar na tabela
     * @param client Código do cliente
     */
    void table3View(double[][] list, String client);

    /**
     * Função responsável por mostrar o resultado da query 4 ao utilizador em forma de tabela por meses e totais
     * @param list Lista com os dados a mostrar na tabela
     * @param product Código do produto
     */
    void table4View(double[][] list, String product);

    /**
     * Função responsável por mostrar o resultado da query E2 ao utilizador em forma de tabela por meses e filiais
     * @param list Lista com os dados a mostrar na tabela
     */
    void tableE2View(double[][] list);

    /**
     * Função responsável por mostrar o resultado da query E2 ao utilizador em forma de tabela por meses e filiais
     * @param list Lista com os dados a mostrar na tabela
     */
    void tableE2View(int[][] list);
}
