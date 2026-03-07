package repo;

import exceptions.LogProgramStateException;
import exceptions.MyException;
import model.states.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class ArrayListRepository implements Repository {
    private final List<ProgramState> programStates = new ArrayList<>();
    private final String logFilePath;

    public ArrayListRepository(String logFilePath) {
        this.logFilePath = logFilePath; //initialized by a string read from the keyboard using Scanner class.
    }

    @Override
    public void addProgramState(ProgramState program) {
        programStates.add(program);
    }

    @Override
    public List<ProgramState> getProgramStates() {
        return programStates;
    }

    @Override
    public void setProgramStates(List<ProgramState> programStates) {
        this.programStates.clear();
        this.programStates.addAll(programStates);
    }

    @Override
    public void logProgramStateExecution(ProgramState programState) throws LogProgramStateException {
        try {
            // print writer -> convenient because it has a lot of functions
            // buffered writer -> good for performance if we re using a lot of write() functions
            // file writer -> low level but we can write into a file
            // append = true => new text will be appended to the end of the file not the beginning
            //nesting these => improved performance overall

            var logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            logFile.println(programState.toString());
            logFile.close();
        } catch (IOException e) {
            throw new LogProgramStateException();
        }
    }

    @Override
    public ProgramState getMainProgram() {
        return programStates.getFirst();
    }

    @Override
    public ProgramState getProgram(int id) {
        return programStates.stream().filter(v -> v.getProgramId() == id).findFirst().orElseThrow();
    }

    @Override
    public int getNumOfPrograms() {
        return programStates.size();
    }
}
