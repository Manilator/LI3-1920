package view;

import static Utils.Constants.N_MONTHS;

/**
 * Classe que representa as tabelas da view
 */
public class Table implements ITable {

    /**
     * Contrutor vazio da classe
     */
    public Table() { }

    /**
     * Função responsável por mostrar o resultado da query 3 ao utilizador em forma de tabela por meses e totais
     * @param list Lista com os dados a mostrar na tabela
     * @param client Código do cliente
     */
    public void table3View(double[][] list, String client)
    {
        if (list != null)
        {
            int columns = N_MONTHS;
            int rows = 3;
            int space = 0;
            int ss = 0;
            String[] _text = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez"};
            String[] _entries = {"Compras", "Prod. Distintos", "Gasto"};

            int i, j, h, v = 0;

            for (j = 0; j < 12; j++)
            {
                if (Math.floor(Math.log10(Math.abs(list[j][2]))) + 3 > space)
                {
                        space = (int) (Math.floor(Math.log10(Math.abs(list[j][2]))) + 3);
                }
            }

            /* Determinar espaço das colunas */
            if (space <= 3)
            {
                space = 5;
            }
            else
            {
                if (space % 2 == 0)
                {
                    space++;
                }
            }

            System.out.println("--------- Cliente " + client);
            /* Imprimir meses */
            System.out.print("               ");
            System.out.print("|");
            for (j = 0; j < columns; j++)
            {
                for (h = 0; h < ((space - 3) / 2); h++)
                    System.out.print(" ");

                System.out.print(_text[j]);

                for (h = 0; h < ((space - 3) / 2); h++)
                    System.out.print(" ");

                System.out.print("|");
            }
            System.out.print("\n");
            System.out.print("---------------+");
            for (i = 0; i < columns; i++)
            {
                for (j = 0; j < space; j++)
                    System.out.print("-");
                System.out.print("+");
            }
            System.out.print("\n");

            /* Inicio da linha com o n da filial*/
            for (i = 0; i < rows; i++)
            {
                System.out.print(_entries[i]);
                if(_entries[i].length() != 15) {
                    for(int l = 0; l < 15 - _entries[i].length(); l++)
                        System.out.print(" ");
                }
                System.out.print("|");
                for (j = 0; j < columns; j++)
                {
                    if (list[j][2] == 0)
                    {
                        ss = 2;
                    }
                    else
                    {
                        ss = (int) (Math.floor(Math.log10(Math.abs(list[j][i]))) + 2);
                    }
                    for (h = 0; h <= (space - ss - 2); h++)
                        System.out.print(" ");
                    System.out.print(String.format("%.1f", list[j][i]));
                    System.out.print("|");
                }
                System.out.print("\n");
            }
        }
        else
        {
            System.out.print("Não existem informações.\n");
        }
    }

    /**
     * Função responsável por mostrar o resultado da query 4 ao utilizador em forma de tabela por meses e totais
     * @param list Lista com os dados a mostrar na tabela
     * @param product Código do produto
     */
    public void table4View(double[][] list, String product)
    {
        if (list != null)
        {
            int columns = N_MONTHS;
            int rows = 3;
            int space = 0;
            int ss = 0;
            String[] _text = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez"};
            String[] _entries = {"Vendas", "Faturado", "Clientes"};

            int i, j, h, v = 0;

            for (j = 0; j < 12; j++)
            {
                if (Math.floor(Math.log10(Math.abs(list[j][1]))) + 3 > space)
                {
                    space = (int) (Math.floor(Math.log10(Math.abs(list[j][1]))) + 3);
                }
            }

            /* Determinar espaço das colunas */
            if (space <= 3)
            {
                space = 5;
            }
            else
            {
                if (space % 2 == 0)
                {
                    space++;
                }
            }

            System.out.println("--------- Produto " + product);
            /* Imprimir meses */
            System.out.print("        ");
            System.out.print("|");
            for (j = 0; j < columns; j++)
            {
                for (h = 0; h < ((space - 3) / 2); h++)
                    System.out.print(" ");

                System.out.print(_text[j]);

                for (h = 0; h < ((space - 3) / 2); h++)
                    System.out.print(" ");

                System.out.print("|");
            }
            System.out.print("\n");
            System.out.print("--------+");
            for (i = 0; i < columns; i++)
            {
                for (j = 0; j < space; j++)
                    System.out.print("-");
                System.out.print("+");
            }
            System.out.print("\n");

            /* Inicio da linha com o n da filial*/
            for (i = 0; i < rows; i++)
            {
                System.out.print(_entries[i]);
                if(_entries[i].length() != 8) {
                    for(int l = 0; l < 8 - _entries[i].length(); l++)
                        System.out.print(" ");
                }
                System.out.print("|");
                for (j = 0; j < columns; j++)
                {
                    if (list[j][2] == 0)
                    {
                        ss = 2;
                    }
                    else
                    {
                        ss = (int) (Math.floor(Math.log10(Math.abs(list[j][i]))) + 2);
                    }
                    for (h = 0; h <= (space - ss - 2); h++)
                        System.out.print(" ");
                    System.out.print(String.format("%.1f", list[j][i]));
                    System.out.print("|");
                }
                System.out.print("\n");
            }
        }
        else
        {
            System.out.print("Não existem informações.\n");
        }
    }

    /**
     * Função responsável por mostrar o resultado da query E2 ao utilizador em forma de tabela por meses e filiais
     * @param list Lista com os dados a mostrar na tabela
     */
    public void tableE2View(double[][] list)
    {
        if (list != null)
        {
            int columns = N_MONTHS;
            int rows = 3;
            int space = 0;
            int ss = 0;
            String[] _text = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez"};
            String[] _entries = {"1", "2", "3"};

            int i, j, h, v = 0;

            for (i = 0; i < rows; i++)
                for (j = 0; j < 12; j++)
                {
                    if (Math.floor(Math.log10(Math.abs(list[j][i]))) + 3 > space)
                    {
                        space = (int) (Math.floor(Math.log10(Math.abs(list[j][i]))) + 3);
                    }
                }

            /* Determinar espaço das colunas */
            if (space <= 3)
            {
                space = 5;
            }
            else
            {
                if (space % 2 == 0)
                {
                    space++;
                }
            }

            /* Imprimir meses */
            System.out.print("  ");
            System.out.print("|");
            for (j = 0; j < columns; j++)
            {
                for (h = 0; h < ((space - 3) / 2); h++)
                    System.out.print(" ");

                System.out.print(_text[j]);

                for (h = 0; h < ((space - 3) / 2); h++)
                    System.out.print(" ");

                System.out.print("|");
            }
            System.out.print("\n");
            System.out.print("--+");
            for (i = 0; i < columns; i++)
            {
                for (j = 0; j < space; j++)
                    System.out.print("-");
                System.out.print("+");
            }
            System.out.print("\n");

            /* Inicio da linha com o n da filial*/
            for (i = 0; i < rows; i++)
            {
                System.out.print(_entries[i]);
                if(_entries[i].length() != 15) {
                    for(int l = 0; l < 2 - _entries[i].length(); l++)
                        System.out.print(" ");
                }
                System.out.print("|");
                for (j = 0; j < columns; j++)
                {
                    if (list[j][i] == 0)
                    {
                        ss = 2;
                    }
                    else
                    {
                        ss = (int) (Math.floor(Math.log10(Math.abs(list[j][i]))) + 2);
                    }
                    for (h = 0; h <= (space - ss - 2); h++)
                        System.out.print(" ");
                    System.out.print(String.format("%.1f", list[j][i]));
                    System.out.print("|");
                }
                System.out.print("\n");
            }
        }
        else
        {
            System.out.print("Não existem informações.\n");
        }
    }

    /**
     * Função responsável por mostrar o resultado da query E2 ao utilizador em forma de tabela por meses e filiais
     * @param list Lista com os dados a mostrar na tabela
     */
    public void tableE2View(int[][] list)
    {
        if (list != null)
        {
            int columns = N_MONTHS;
            int rows = list.length;
            int space = 0;
            int ss = 0;
            String[] _text = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez"};
            String[] _entries = {"1", "2", "3"};

            int i, j, h, v = 0;

            for (i = 0; i < rows; i++)
                for (j = 0; j < columns; j++)
                {
                    if (Math.floor(Math.log10(Math.abs(list[i][j]))) + 3 > space)
                    {
                        space = (int) (Math.floor(Math.log10(Math.abs(list[i][j]))) + 3);
                    }
                }

            /* Determinar espaço das colunas */
            if (space <= 3)
            {
                space = 5;
            }
            else
            {
                if (space % 2 == 0)
                {
                    space++;
                }
            }

            /* Imprimir meses */
            System.out.print("  ");
            System.out.print("|");
            for (j = 0; j < columns; j++)
            {
                for (h = 0; h < ((space - 3) / 2); h++)
                    System.out.print(" ");

                System.out.print(_text[j]);

                for (h = 0; h < ((space - 3) / 2); h++)
                    System.out.print(" ");

                System.out.print("|");
            }
            System.out.print("\n");
            System.out.print("--+");
            for (i = 0; i < columns; i++)
            {
                for (j = 0; j < space; j++)
                    System.out.print("-");
                System.out.print("+");
            }
            System.out.print("\n");

            /* Inicio da linha com o n da filial*/
            for (i = 0; i < rows; i++)
            {
                System.out.print(_entries[i]);
                if(_entries[i].length() != 15) {
                    for(int l = 0; l < 2 - _entries[i].length(); l++)
                        System.out.print(" ");
                }
                System.out.print("|");
                for (j = 0; j < columns; j++)
                {
                    if (list[i][j] == 0)
                    {
                        ss = 2;
                    }
                    else
                    {
                        ss = (int) (Math.floor(Math.log10(Math.abs(list[i][j]))) + 2);
                    }
                    for (h = 0; h <= (space - ss); h++)
                        System.out.print(" ");
                    System.out.print(list[i][j]);
                    System.out.print("|");
                }
                System.out.print("\n");
            }
        }
        else
        {
            System.out.print("Não existem informações.\n");
        }
    }

}
