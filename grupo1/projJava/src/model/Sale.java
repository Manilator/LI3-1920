package model;

import java.math.BigDecimal;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static Utils.Constants.N_BRANCHES;

public class Sale implements ISale {
    private String  product; /**< Código de produto */
    private String  client; /**< Código de cliente */
    private double price; /**< Preço do produto */
    private int     units; /**< Número de unidades vendidas */
    private char    promotion; /**< Tipo de promoção N ou P */
    private int     month; /**< Número do mês */
    private int     branch; /**< Número da filial */

    /**
     * Construtor com String para a classe
     * @param sale_line Linha com informacao de uma venda
     */
    public Sale(String sale_line) {
        String[] saleGroups = sale_line.split(" ");
        if(saleGroups.length != 7) this.price = -1;
        else {
            this.product = saleGroups[0];
            this.price = Double.parseDouble(saleGroups[1]);
            this.units = Integer.parseInt(saleGroups[2]);
            this.promotion = saleGroups[3].toCharArray()[0];
            this.client = saleGroups[4];
            this.month = Integer.parseInt(saleGroups[5]);
            this.branch = Integer.parseInt(saleGroups[6]);
        }
    }

    /**
     * Verifica se uma venda é válida
     * @return True se a venda for válida e False se for inválida
     */
    public boolean validSale() {
        return this.price >= 0
                && this.price<= 999.99
                && this.units >= 0
                && this.units <= 250
                && month <= 12
                && month >= 1
                && this.branch > 0
                && this.branch <= N_BRANCHES;
    }

    /**
     * Get product
     * @return Devolve o código do produto
     */
    public String getProduct() {
        return product;
    }

    /**
     * Get client
     * @return Devolve o código do cliente
     */
    public String getClient() {
        return client;
    }

    /**
     * Get price
     * @return Devolve o preço
     */
    public double getPrice() {
        return price;
    }

    /**
     * Get units
     * @return Devolve o número de unidades vendidas
     */
    public int getUnits() {
        return units;
    }

    /**
     * Get promotion
     * @return Devolve o tipo de promoção
     */
    public char getPromotion() {
        return promotion;
    }

    /**
     * Get month
     * @return Devolve o mês
     */
    public int getMonth() {
        return month;
    }

    /**
     * Get branch
     * @return Devolve o número da filial
     */
    public int getBranch() {
        return branch;
    }
}