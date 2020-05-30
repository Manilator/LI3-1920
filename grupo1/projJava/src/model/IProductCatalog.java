package model;

import java.util.List;
import java.util.Map;

public interface IProductCatalog {

    /**
     * Função que insere um produto a estrutura product caso o código seja válido
     * @param productCode Código do produto
     * @return True, caso tenha sido inserido (código válido), False caso contrário
     */
    public boolean insertProduct(String productCode);

    /**
     * Verifica se o produto existe
     * @param code Código de produto
     * @return True se o código existir, False se não existir
     */
    public boolean existProduct(String code);

    /**
     * Devolve o tamanho da estrutura products
     * @return Tamanho da estrutura products
     */
    public int getSize();

    /**
     * Devolve uma lista de produtos não comprados
     * @param allProductsBought Map com todos os produtos comprados
     * @return List de Strings com os códigos dos produtos não comprados
     */
    List<String> getProductsNotBought(Map<String,String> allProductsBought);
}