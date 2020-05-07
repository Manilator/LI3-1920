import controller.Controller;

public class Main {
    public static void main(String[] args) {
        System.out.println("Starting Main!\n----------");

        Controller controller = new Controller();

        if (args.length == 0) {
            controller.startController();
        }
        System.out.println("Closing Main!\n----------");
    }
}
