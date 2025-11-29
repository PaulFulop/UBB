package view;
import java.util.*;

public class TextMenu {
    private final Map<String, Command> commands;
    public TextMenu(){
        commands = new LinkedHashMap<>();
    }

    public void addCommand(Command command){
        commands.put(command.getKey(), command);
    }

    public void printCommands(){
        IO.println("\nCommands:\n");
        for (var command : commands.values()){
            String line = String.format("%4s : %s", command.getKey(), command.getDescription());
            IO.println(line);
        }
    }

    public void show(){

        Scanner scanner = new Scanner(System.in);
        while(true){
            printCommands();
            IO.print("Input the option: ");
            String key = scanner.nextLine();
            Command com = commands.get(key);

            if (com == null){
                System.out.println("Invalid Option");
                continue;
            }
            com.execute();
        }
    }
}
