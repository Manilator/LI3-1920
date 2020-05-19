package Utils;

import java.util.regex.Pattern;

public class Constants {

    public static final String ClientsPath = "data/Clientes.txt";
    public static final String ProductsPath = "data/Produtos.txt";
    public static final String SalesPath = "data/Vendas_1M.txt";
    public static final String SalesPath3M = "data/Vendas_3M.txt";
    public static final String SalesPath5M = "data/Vendas_5M.txt";
    public static final int N_MONTHS = 12;
    public static final int N_BRANCHES = 3;
    public static final int N_TYPES = 2;
    public static final int N = 0;
    public static final int P = 1;
    public static final Pattern clientPattern = Pattern.compile("[A-Z]([0-4]\\d{3}|50{3})");
    public static final Pattern productPattern = Pattern.compile("[A-Z][A-Z]([0-4]\\d{3}|50{3})");
}
