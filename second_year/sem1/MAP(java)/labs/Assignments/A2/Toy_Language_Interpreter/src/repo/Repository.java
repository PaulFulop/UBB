package repo;

import exceptions.LogProgramStateException;
import exceptions.MyException;
import model.states.ProgramState;

import java.util.List;

public interface Repository {
    void addProgramState(ProgramState program);
    List<ProgramState> getProgramStates();
    void setProgramStates(List<ProgramState> programStates);
    void logProgramStateExecution(ProgramState programState) throws LogProgramStateException;
}
