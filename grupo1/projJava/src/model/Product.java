package model;

import java.util.regex.Matcher;

import static Utils.Constants.*;

public class Product implements IProduct {
    private final char first_letter;
    private final char second_letter;
    private final int number;

    public Product(char first_letter, char second_letter, int number) {
        this.first_letter = first_letter;
        this.second_letter = second_letter;
        this.number = number;
    }

    public Product (String productCode) {
        this.first_letter = productCode.charAt(0);
        this.second_letter = productCode.charAt(1);
        this.number = Integer.parseInt(productCode.substring(2));
    }

    public Product(Product product) {
        this.first_letter = product.getFirst_letter();
        this.second_letter = product.getSecond_letter();
        this.number = product.getNumber();
    }

    String getProductCode() {
        StringBuilder id = new StringBuilder();
        id.append(this.first_letter);
        id.append(this.second_letter);
        id.append(String.valueOf(this.number));
        return id.toString();
    }

    public boolean validate() {
        Matcher e = productPattern.matcher(getProductCode());
        return e.matches();
    }

    Product newProduct(String productCode) {
        return new Product(productCode.charAt(0), productCode.charAt(1), Integer.parseInt(productCode.substring(2)));
    }

    Boolean equalsProduct(Product a, Product b) {
        return (a.getFirst_letter() == b.getFirst_letter() &&
                a.getSecond_letter() == b.getSecond_letter() &&
                a.getNumber() == b.getNumber());
    }

    public char getFirst_letter() {
        return first_letter;
    }

    public char getSecond_letter() {
        return second_letter;
    }

    public int getNumber() {
        return number;
    }
/*
    public boolean validate() {
        return (this.first_letter >= 'A' && this.first_letter <= 'Z' &&
                this.second_letter >= 'A' && this.second_letter <= 'Z' &&
                this.number >= 1000 && this.number <= 9999);
    }*/

    /*
    void destroyProduct(Product product) {
        free(product);
    }*/

}
