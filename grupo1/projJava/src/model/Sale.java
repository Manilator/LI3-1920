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
/*
    public Sale(String sale_line) {
        String pattern = "([A-Z][A-Z](1000|5000|[1-4][0-9][0-9][0-9]))\\ (0.0|999.99|[1-9][0-9]?[0-9]?\\.[0-9][0-9]?|0\\.[0-9][0-9])\\ ([1-2][0-9][0-9]|[1-9][0-9]|[1-9])\\ (N|P)\\ ([A-Z](1000|5000|[1-4][0-9][0-9][0-9]))\\ (1[0-2]|[1-9])\\ ([1-3])";
        Pattern r = Pattern.compile(pattern);
        Matcher m = r.matcher(sale_line);
        if (m.find()) {
            this.product = m.group(1);
            this.price = new BigDecimal(m.group(3));
            this.units = Integer.parseInt(m.group(4));
            this.promotion = m.group(5).charAt(0);
            this.client = m.group(6);
            this.month = Integer.parseInt(m.group(8));
            this.branch = Integer.parseInt(m.group(9));
        }
    }
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

    public String getProduct() {
        return product;
    }

    public String getClient() {
        return client;
    }

    public double getPrice() {
        return price;
    }

    public int getUnits() {
        return units;
    }

    public char getPromotion() {
        return promotion;
    }

    public int getMonth() {
        return month;
    }

    public int getBranch() {
        return branch;
    }
}
