package model;

import java.util.List;
import java.util.Map;

/**
 * Interface da classe que representa o catalogo de produtos
 */
public interface IProductCatalog {

    /**
     * Função que insere um produto a estrutura product caso o código seja válido
     * @param productCode Código do produto
     * @return True, caso tenha sido inserido (código válido), False caso contrário
     */
    boolean insertProduct(String productCode);

    /**
     * Verifica se o produto existe
     * @param code Código de produto
     * @return True se o código existir, False se não existir
     */
    boolean existProduct(String code);

    /**
     * Devolve o tamanho da estrutura products
     * @return Tamanho da estrutura products
     */
    int getSize();

    /**
     * Devolve uma lista de produtos não comprados
     * @param allProductsBought Map com todos os produtos comprados
     * @return List de Strings com os códigos dos produtos não comprados
     */
    List<String> getProductsNotBought(Map<String,String> allProductsBought);
}