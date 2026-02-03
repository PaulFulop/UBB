package model.states;


import exceptions.ProgramException;
import model.statements.StatementInterface;
import model.states.list.OutList;
import model.states.map.tables.*;
import model.states.stack.ExecutionStack;

public final class ProgramState {
    private static int globalIdCounter = 0;
    private final int programId;
    private final ExecutionStack exeStack;
    private final SymbolTable symTable;
    private final OutList out;
    private final FileTable fileTable;
    private final HeapTable heapTable;
    private final BarrierTable barrierTable;
    private final LockTable lockTable;
    private final LatchTable latchTable;
    private final SemaphoreTable semaphoreTable;

    public ProgramState(ExecutionStack exeStack, SymbolTable symTable,
                        OutList out, FileTable fileTable,
                        HeapTable heapTable, BarrierTable barrierTable,
                        LockTable lockTable, LatchTable latchTable, SemaphoreTable semaphoreTable) {
        this.programId = generateId();
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.fileTable = fileTable;
        this.heapTable = heapTable;
        this.barrierTable = barrierTable;
        this.lockTable = lockTable;
        this.latchTable = latchTable;
        this.semaphoreTable = semaphoreTable;
    }

    private static synchronized int generateId() {
        return globalIdCounter++;
    }

    @Override
    public String toString() {
        return "-------------------------------------------------------" +
                "\n PROGRAM ID: " + programId +
                "\nEXECUTION STACK:\n" + exeStack.toString() +
                "\nSYMBOL TABLE:\n" + symTable.toString() +
                "\nOUT:\n" + out.toString() +
                "\nFILE TABLE\n" + fileTable.toString() +
                "\nHEAP TABLE:\n" + heapTable.toString() +
                "\nBARRIER TABLE:\n" + barrierTable.toString() +
                "\nLOCK TABLE:\n" + lockTable.toString() +
                "\nLATCH TABLE:\n" + latchTable.toString() +
                "\nSEMAPHORE TABLE\n"+ semaphoreTable.toString()+
                "\n-------------------------------------------------------\n\n";
    }

    public boolean isNotCompleted() {
        return !exeStack.isEmpty();
    }

    public ProgramState executeOneStep() throws ProgramException {
        ExecutionStack executionStack = this.exeStack();
        if (executionStack.isEmpty()) throw new ProgramException("The execution stack of the program is empty");

        StatementInterface nextStatement = executionStack.pop();
        return nextStatement.execute(this);
    }

    public int getProgramId(){
        return programId;
    }
    public ExecutionStack exeStack() {
        return exeStack;
    }
    public SymbolTable symTable() {
        return symTable;
    }
    public OutList out() {
        return out;
    }
    public FileTable fileTable() {
        return fileTable;
    }
    public HeapTable heapTable() {
        return heapTable;
    }
    public BarrierTable barrierTable() {return barrierTable;}
    public LockTable lockTable() {return lockTable;}
    public LatchTable latchTable() {return latchTable;}
    public SemaphoreTable semaphoreTable() {return semaphoreTable;}
}

