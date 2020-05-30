package view;

import java.util.List;

public class Pages implements IPages {

    private int size;
    private int elem_per_page;
    private List<String> list;
    private IGestVendasView view;

    public Pages(int size, int elem_per_page, List<String> list) {
        this.size = size;
        this.elem_per_page = elem_per_page;
        this.list = list;
        this.view = new GestVendasView();
    }


    public void show(int page) {
        int max = (int) Math.ceil(this.size / this.elem_per_page);
        if (this.size % this.elem_per_page == 0)
            max--;
        int i;
        int j = 0;

        if (page > max)
            page = max;
        else if (page < 0)
            page = 0;

        view.printMessage("--------- Página " + page + " de " + max + " ---------");
        for (i = page * elem_per_page, j = 0; j < elem_per_page && i < this.size; i++, j++)
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
