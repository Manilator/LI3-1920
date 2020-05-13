package model;

public class InfoClient {

    private int unitsN; /**< Número de unidades do tipo N */
    private int unitsP; /**< Número de unidades do tipo P */

    public InfoClient() {
        this.unitsN = 0;
        this.unitsP = 0;
    }

    public void updateInfoClient(int units, char promotion_type) {
        if (promotion_type == 'P') {
            this.unitsP += units;
        } else if (promotion_type == 'N') {
            this.unitsN += units;
        }
    }
}
