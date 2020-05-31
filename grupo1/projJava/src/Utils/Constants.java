package Utils;

import java.util.regex.Pattern;

/**
 * Classe auxiliar Constants
 */
public class Constants {

    public static final String DefaultClientsPath = "data/Clientes.txt";
    public static final String DefaultProductsPath = "data/Produtos.txt";
    public static final String DefaultSalesPath = "data/Vendas_1M.txt";
    public static final int N_MONTHS = 12;
    public static final int N_BRANCHES = 3;
    public static final int ELEMENTS_PER_PAGE = 10;
    public static final Pattern clientPattern = Pattern.compile("[A-Z]([0-4]\\d{3}|50{3})");
    public static final Pattern productPattern = Pattern.compile("[A-Z][A-Z]([0-4]\\d{3}|50{3})");
}
