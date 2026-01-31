package controller;

import exceptions.ProgramException;
import exceptions.TypecheckException;
import model.states.*;
import model.statements.StatementInterface;
import model.types.Type;
import repo.Repository;

import java.util.List;
import java.util.Objects;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;


public final class ProgramService {
    private final Repository repo;
    private final GarbageCollector garbageCollector;
    private ExecutorService executor;

    public ProgramService(Repository repo) {
        this.repo = repo;
        this.garbageCollector = new GarbageCollector();
        this.executor = Executors.newFixedThreadPool(2); // good when using gui
    }

    public ExecutorService getExecutor() {
        return executor;
    }

    public GarbageCollector getGarbageCollector(){
        return garbageCollector;
    }

    public Repository getRepo() {
        return repo;
    }

    public void addNewProgram(StatementInterface program) {
        try{
            // typechecking before being able to even run the program / execute thread after fork
            MyMap<String, Type> initialTypeTable = new MyMap<>();
            program.typecheck(initialTypeTable);

            var executionStack = new MyStack<StatementInterface>();
            executionStack.push(program);
            repo.addProgramState(new ProgramState(
                    executionStack,
                    new MyMap<>(),
                    new MyList<>(),
                    new MyMap<>(),
                    new MyHeap()));
        }
        catch (TypecheckException e){
            IO.print(e.getMessage());
            System.exit(1);
        }
    }

    public void executeOneStepForAllPrograms(List<ProgramState> programStates) throws InterruptedException, ProgramException {
        // log the execution of a program and also for it's threads
        programStates.forEach(repo::logProgramStateExecution);

        //RUN concurrently one step for each of the existing PrgStates
        //-----------------------------------------------------------------------

        //prepare the list of callables
        List<Callable<ProgramState>> callList = programStates.stream()
                .map((ProgramState p) -> (Callable<ProgramState>) (p::executeOneStep))
                .collect(Collectors.toList());

        //start the execution of the callables
        //it returns the list of new created PrgStates (namely threads)
        List<ProgramState> newProgramStatesList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (Exception e) {
                        throw new ProgramException(e.getMessage());
                    }
                }).filter(Objects::nonNull)
                .toList();

        //add the new created threads to the list of existing threads
        programStates.addAll(newProgramStatesList);

        //after the execution, print the Program State List into the log file
        programStates.forEach(repo::logProgramStateExecution);

        //Save the current programs in the repository
        repo.setProgramStates(programStates);
    }

    public void executeMainProgram() throws ProgramException, InterruptedException {
        executor = Executors.newFixedThreadPool(2);

        List<ProgramState> programStates = removeCompletedPrograms(repo.getProgramStates());
        while (!programStates.isEmpty()) {
            var allSymbolTables = programStates.stream()
                    .map(ProgramState::symTable)
                    .toList();

            garbageCollector.run(allSymbolTables, programStates.getFirst().heapTable());
            executeOneStepForAllPrograms(programStates);
            programStates = removeCompletedPrograms(repo.getProgramStates());
        }

        executor.shutdownNow();
        //HERE the repository still contains at least one Completed Prg
        // and its List<PrgState> is not empty. Note that oneStepForAllPrg calls the method
        //setPrgList of repository in order to change the repository

        // update the repository state
        repo.setProgramStates(programStates);
    }

    public List<ProgramState> removeCompletedPrograms(List<ProgramState> programStates) {

        return programStates.stream().
                filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList());
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (obj == null || obj.getClass() != this.getClass()) return false;
        var that = (ProgramService) obj;
        return Objects.equals(this.repo, that.repo) &&
                Objects.equals(this.garbageCollector, that.garbageCollector) &&
                Objects.equals(this.executor, that.executor);
    }

    @Override
    public int hashCode() {
        return Objects.hash(repo, garbageCollector, executor);
    }

    @Override
    public String toString() {
        return "ProgramService[" +
                "repo=" + repo + ", " +
                "garbageCollector=" + garbageCollector + ", " +
                "executor=" + executor + ']';
    }

}
