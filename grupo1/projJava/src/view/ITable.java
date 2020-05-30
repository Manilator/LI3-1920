package view;

public interface ITable {

    /**
     * Função responsável por mostrar o resultado da query 3 ao utilizador em forma de tabela (?) (!!!)
     * @param list (!!!)
     * @param client Código do cliente
     */
    public void table3View(double[][] list, String client);

    /**
     * Função responsável por mostrar o resultado da query 4 ao utilizador em forma de tabela (?) (!!!)
     * @param list (!!!)
     * @param product Código do produto
     */
    public void table4View(double[][] list, String product);
}
