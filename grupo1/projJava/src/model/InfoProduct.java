package model;

import java.io.Serializable;
import java.util.Arrays;

import static Utils.Constants.N_MONTHS;

/**
 * Classe que contem a informacao de um dado produto
 */
public class InfoProduct implements IInfoProduct, Serializable {

    private static final long serialVersionUID = -677107323861266485L;
    private int[] quantities;
    private double[] totalBilled;

    /**
     * Construtor vazio da classe
     */
    public InfoProduct() {
        this.quantities = new int[12];
        this.totalBilled = new double[12];
        Arrays.fill(this.totalBilled, 0);
    }

    /**
     * Função que atualiza a estrutura InfoProduct com as informações dadas (!!!) confirmar pls
     * @param quantity quantidade comprada do produto a ser somada à estrutura
     * @param billed montante faturado com a compra do produto a ser somada à estrutura
     * @param month mês que vai determinar a posição onde as informações serão somadas à estrutura
     */
    public void updateInfoProduct(int quantity, double billed, int month) {
        this.quantities[month-1] += quantity;
        this.totalBilled[month-1] += billed;
    }

    /**
     * Devolve o numero de produtos comprados em cada mês
     * @return Array de inteiros com o numero de produtos comprados
     */
    public int[] getQuantities() {
        return this.quantities.clone();
    }

    /**
     * Devolve a quantidade de compras do produto no ano inteiro
     * @return Int com a quantidade comprada do produto no ano inteiro
     */
    public int getTotalQuantity(){
        int result = 0;

        for (int i=0;i<N_MONTHS;i++)
            result += this.quantities[i];

        return result;
    }
}
