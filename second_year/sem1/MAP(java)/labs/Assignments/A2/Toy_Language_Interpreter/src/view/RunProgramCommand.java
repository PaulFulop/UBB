package view;

import controller.Controller;

public class RunProgramCommand extends Command {
    private final Controller controller;
    public RunProgramCommand(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try{
            controller.executeMainProgram();
        }
        catch(Exception e){
            IO.println(e.getMessage());
        }
    }
}
