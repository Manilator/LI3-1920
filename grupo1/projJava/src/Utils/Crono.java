package Utils;

import static java.lang.System.nanoTime;

/**
 * Classe auxiliar Crono
 */
public class Crono {

    private static long inicio = 0L;
    private static long fim = 0L;

    /**
     * Começa a contar o tempo
     */
    public static void start() {
        fim = 0L; inicio = nanoTime();
    }

    /**
     * Para de contar o tempo e devolve quanto demorou
     * @return Tempo demorado
     */
    public static double stop() {
        fim = nanoTime();
        long elapsedTime = fim - inicio;
        // segundos
        return elapsedTime / 1.0E09;
    }

    /**
     * Devolve o tempo demorado
     * @return String com o tempo demorado
     */
    public static String getTime() {
        return "" + stop();
    }

    /**
     * Devolve a frase a apresentar com o tempo que demorou
     * @return String formatada com o tempo demorado
     */
    public static String getTimeString() {
        return "Elapsed Time: " +getTime() + " s";
    }
}