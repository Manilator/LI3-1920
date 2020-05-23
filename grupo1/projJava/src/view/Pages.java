package view;

import java.util.List;

import static Utils.Constants.ELEMENTS_PER_PAGE;

public class Pages implements IPages {

    private int size;
    private List<String> list;
    private IGestVendasView view;

    public Pages(int size, List<String> list) {
        this.size = size;
        this.list = list;
        this.view = new GestVendasView();
    }


    public void show(int page) {
        int max = this.size / ELEMENTS_PER_PAGE;
        int i;
        int j = 0;

        if (page > max)
            page = max;
        else if (page < 0)
            page = 0;

        view.printMessage("--------- Página " + page + " de " + max + " ---------");
        for (i = page * 10, j = 0; j < ELEMENTS_PER_PAGE && i < this.size; i++, j++)
        {
            view.printMessage(String.valueOf(this.list.get(i)));
        }
        view.printMessage("--------- Página " + page + " de " + max + " ---------");
    }

    public void choices() {
        view.printMessage("n - Próxima página");
        view.printMessage("c - Página anterior");
        view.printMessage("c - Escolher página");
        view.printMessage("* - Voltar ao menu");
    }

}
