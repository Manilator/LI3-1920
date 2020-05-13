package model;

import java.util.ArrayList;
import java.util.Hashtable;

public class Billing {

    private int n_sales; /**< Número de Vendas */
    private double totalBilled; /**< Total faturado */
    private int unitiesP; /**< Unidades P vendidas */
    private int unitiesN; /**< Unidades N vendidas */
    private ArrayList<Double> branchesBilling; /**< Faturação dividida por filiais */
    private ArrayList<Integer> branchesNSales; /**< Número de vendas dividida por filiais */
    private Hashtable<String, BillingProduct> billingsProduct; /**< Faturação dividida por produtos */

}
