package model;

import java.util.regex.Matcher;

import static Utils.Constants.*;

public class Product implements IProduct
{
    private final String productCode;

    public Product (String productCode) {
        this.productCode = productCode;
    }

    /**
     * Valida um produto
     * @return String com o código de produto
     */
    public boolean validate() {
        Matcher e = productPattern.matcher(this.productCode);
        return e.matches();
    }
}
