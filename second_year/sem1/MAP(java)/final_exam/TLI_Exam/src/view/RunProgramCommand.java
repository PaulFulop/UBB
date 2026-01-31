package view;

import controller.ProgramService;

public class RunProgramCommand extends Command {
    private final ProgramService controller;
    public RunProgramCommand(String key, String description, ProgramService controller) {
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
