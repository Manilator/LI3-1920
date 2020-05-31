package model;

import java.io.Serializable;
import java.util.Arrays;

import static Utils.Constants.N_MONTHS;

/**
 * Classe que contem a informacao de um dado cliente
 */
public class InfoClient implements IInfoClient, Serializable {

    private static final long serialVersionUID = -3123923576348809853L;
    private int[] unitsN;
    private int[] unitsP;
    private double totalBilled;


    /**
     * Construtor vazio da classe
     */
    public InfoClient() {
        this.unitsN = new int[N_MONTHS];
        this.unitsP = new int[N_MONTHS];
        this.totalBilled = 0;
        Arrays.fill(unitsN,0);
        Arrays.fill(unitsP,0);
    }

    /**
     * Função que atualiza a estrutura InfoClient com as informações dadas (!!!) confirmar pls
     * @param units unidades compradas pelo cliente a ser somada à estrutura
     * @param promotion_type tipo de promoção da compra
     * @param month mês que vai determinar a posição onde as informações serão somadas à estrutura
     * @param totalBilled montante faturado com a compra do produto a ser somada ao total faturado
     */
    public void updateInfoClient(int units, char promotion_type, int month, double totalBilled) {
        if (promotion_type == 'P') {
            this.unitsP[month-1] += units;
        } else if (promotion_type == 'N') {
            this.unitsN[month-1] += units;
        }
        this.totalBilled += totalBilled;
    }

    /**
     * Recolhe se um cliente realizou a compra de um produto por mês
     * @return Array de booleanos em que cada entrada corresponde aos meses
     */
    public boolean[] didPurchaseMonth() {
        boolean[] months = new boolean[N_MONTHS];
        for(int i = 0; i < N_MONTHS; i++) {
            months[i] = this.unitsP[i] != 0 || this.unitsN[i] != 0;
        }
        return months;
    }

    /**
     * Calcula o total gasto
     * @return Total gasto
     */
    public double getTotalBilled() {
        return totalBilled;
    }

    /**
     * Calcula o total de unidades
     * @return Total de unidades
     */
    public int getTotalUnits() {
        return Arrays.stream(unitsN).sum() + Arrays.stream(unitsP).sum();
    }
}
