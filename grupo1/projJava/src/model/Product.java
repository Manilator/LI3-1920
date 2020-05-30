package model;

import java.io.Serializable;
import java.util.regex.Matcher;

import static Utils.Constants.productPattern;

public class Product implements IProduct, Serializable {
    private static final long serialVersionUID = -8818347045121551911L;
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
