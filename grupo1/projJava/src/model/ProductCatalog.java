package model;

import java.io.Serializable;

import java.util.Collections;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Classe que representa o catalogo de produtos
 */
public class ProductCatalog implements IProductCatalog, Serializable {

    private static final long serialVersionUID = -885894091262755264L;
    private Map<String,IProduct> products;

    /**
     * Construtor vazio da classe
     */
    public ProductCatalog() {
        products = new HashMap<>();
    }

    /**
     * Função que insere um produto a estrutura product caso o código seja válido
     * @param productCode Código do produto
     * @return True, caso tenha sido inserido (código válido), False caso contrário
     */
    public boolean insertProduct(String productCode){
        Product product = new Product(productCode);
        if (product.validate()) {
            this.products.put(productCode, product);
            return true;
        }
        return false;
    }

    /**
     * Devolve o tamanho da estrutura products
     * @return Tamanho da estrutura products
     */
    public int getSize() {
        return this.products.size();
    }

    /**
     * Verifica se o produto existe
     * @param code Código de produto
     * @return True se o código existir, False se não existir
     */
    public boolean existProduct(String code) {
        return this.products.containsKey(code);
    }

    /**
     * Devolve uma lista de produtos não comprados
     * @param allProductsBought Map com todos os produtos comprados
     * @return List de Strings com os códigos dos produtos não comprados
     */
    public List<String> getProductsNotBought(Map<String,String> allProductsBought){
        List<String> result = new ArrayList<>();

        for (Map.Entry<String, IProduct> entry : products.entrySet())
            if(!allProductsBought.containsKey(entry.getKey()))
                result.add(entry.getKey());
        Collections.sort(result);
        return result;
    }
}
