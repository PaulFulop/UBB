package model.states;


import exceptions.ProgramException;
import model.statements.StatementInterface;
import model.states.list.OutList;
import model.states.map.tables.FileTable;
import model.states.map.tables.HeapTable;
import model.states.map.tables.LockTable;
import model.states.map.tables.SymbolTable;
import model.states.stack.ExecutionStack;

public final class ProgramState {
    private static int globalIdCounter = 0;
    private final int programId;
    private final ExecutionStack exeStack;
    private final SymbolTable symTable;
    private final OutList out;
    private final FileTable fileTable;
    private final HeapTable heapTable;
    private final LockTable lockTable;

    public ProgramState(ExecutionStack exeStack, SymbolTable symTable,
                        OutList out, FileTable fileTable,
                        HeapTable heapTable, LockTable lockTable) {
        this.programId = generateId();
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.fileTable = fileTable;
        this.heapTable = heapTable;
        this.lockTable = lockTable;
    }

    private static synchronized int generateId() {
        return globalIdCounter++;
    }

    @Override
    public String toString() {
        return  "----------------------------------------------------------" +
                "\n PROGRAM ID: " + programId +
                "\nEXECUTION STACK:\n" + exeStack.toString() +
                "\nSYMBOL TABLE:\n" + symTable.toString() +
                "\nOUT:\n" + out.toString() +
                "\nFILE TABLE\n" + fileTable.toString() +
                "\nHEAP TABLE:\n" + heapTable.toString() +
                "\nLOCK TABLE\n" +  lockTable.toString() +
                "----------------------------------------------------------\n\n";
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
    public LockTable lockTable() {return lockTable;}
}

