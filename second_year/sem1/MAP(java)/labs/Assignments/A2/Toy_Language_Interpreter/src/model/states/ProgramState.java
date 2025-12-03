package model.states;


import exceptions.ProgramException;
import model.statements.StatementInterface;

public final class ProgramState {
    private static int globalIdCounter = 0;
    private final int programId;
    private final ExecutionStackInterface exeStack;
    private final SymbolTableInterface symTable;
    private final OutInterface out;
    private final FileTableInterface fileTable;
    private final Heap heapTable;

    public ProgramState(ExecutionStackInterface exeStack, SymbolTableInterface symTable, OutInterface out, FileTableInterface fileTable, Heap heapTable) {
        this.programId = generateId();
        this.exeStack = exeStack;
        this.symTable = symTable;
        this.out = out;
        this.fileTable = fileTable;
        this.heapTable = heapTable;
    }

    private static synchronized int generateId() {
        return globalIdCounter++;
    }

    @Override
    public String toString() {
        return "\n PROGRAM ID: " + programId +
                "\nEXECUTION STACK:\n" + exeStack.toString() +
                "\nSYMBOL TABLE:\n" + symTable.toString() +
                "\nOUT:\n" + out.toString() +
                "\nFILE TABLE\n" + fileTable.toString() +
                "\nHEAP TABLE:\n" + heapTable.toString() +
                "\n\n";
    }

    public boolean isNotCompleted() {
        return !exeStack.isEmpty();
    }

    public ProgramState executeOneStep() throws ProgramException {
        ExecutionStackInterface executionStack = this.exeStack();
        if (executionStack.isEmpty()) throw new ProgramException("The execution stack of the program is empty");

        StatementInterface nextStatement = executionStack.pop();
        return nextStatement.execute(this);
    }

    public ExecutionStackInterface exeStack() {
        return exeStack;
    }

    public SymbolTableInterface symTable() {
        return symTable;
    }

    public OutInterface out() {
        return out;
    }

    public FileTableInterface fileTable() {
        return fileTable;
    }

    public Heap heapTable() {
        return heapTable;
    }


}

