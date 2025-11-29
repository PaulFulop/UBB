package view;

public class ExitCommand extends Command {
    public ExitCommand(String key, String description) {
        super(key, description);
    }

    @Override
    public void execute() {
        IO.println("Bye!");
        System.exit(0);
    }
}
