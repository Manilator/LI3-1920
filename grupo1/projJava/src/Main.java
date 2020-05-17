import controller.Controller;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        System.out.println("Starting Main!\n----------");

        Controller controller = new Controller();

        if (args.length == 0) {
            controller.startController();
        }
        System.out.println("Closing Main!\n----------");
    }
}
