package controller;

import exceptions.MyException;
import exceptions.ProgramException;
import model.states.*;
import model.statements.StatementInterface;
import repo.Repository;

import java.util.List;
import java.util.stream.Collectors;


public record Controller(Repository repo, GarbageCollector garbageCollector) {
    public void addNewProgram(StatementInterface program) {
        var executionStack = new LinkedListExecutionStack();
        executionStack.push(program);
        repo.addProgramState(new ProgramState(
                0,
                executionStack,
                new MapSymbolTable(),
                new ArrayListOut(),
                new MapFileTable(),
                new Heap()));
    }

    public void executeMainProgram() throws ProgramException {
        var programState = repo.getPrgList().getFirst();
        repo.logProgramStateExecution(programState);
        while (programState.isNotCompleted()) {
            programState.executeOneStep();
            repo.logProgramStateExecution(programState);
            garbageCollector.run(programState.symTable(), programState.heapTable());
        }
    }

    List<ProgramState> removeCompletedPrograms(List<ProgramState> programStates){

        return programStates.stream().
                filter(e -> e.isNotCompleted())
                .collect(Collectors.toList());
    }
}
