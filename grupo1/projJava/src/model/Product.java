package model;

public class Product {
    private final char first_letter;
    private final char second_letter;
    private final int number;

    public Product(char first_letter, char second_letter, int number) {
        this.first_letter = first_letter;
        this.second_letter = second_letter;
        this.number = number;
    }

    String getProductCode(Product product) {
        return String.format("%c%c%d",product.getFirst_letter(),product.getSecond_letter(),product.getNumber());
    }

    public Boolean verifyProduct(String productCode) {
        int number = Integer.parseInt(productCode.substring(2));
        char first_letter = productCode.charAt(0);
        char second_letter = productCode.charAt(1);
        return (number >= 1000 && number <= 9999) &&
                (first_letter >= 'A' && first_letter <= 'Z') &&
                (second_letter >= 'A' && second_letter <= 'Z');
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
    void destroyProduct(Product product) {
        free(product);
    }*/

}
