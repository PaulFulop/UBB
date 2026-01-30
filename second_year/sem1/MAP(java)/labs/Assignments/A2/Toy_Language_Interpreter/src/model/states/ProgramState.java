package model.states;


import exceptions.ProgramException;
import model.statements.StatementInterface;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;

public final class ProgramState {
    private static int globalIdCounter = 0;
    private final int programId;
    private final MyStack<StatementInterface> exeStack;
    private final MyMap<String, Value> symTable;
    private final MyList<Value> out;
    private final MyMap<StringValue, BufferedReader> fileTable;
    private final MyHeap heapTable;

    public ProgramState(MyStack<StatementInterface> exeStack, MyMap<String, Value> symTable, MyList<Value> out, MyMap<StringValue, BufferedReader> fileTable, MyHeap heapTable) {
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
        MyStack<StatementInterface> executionStack = this.exeStack();
        if (executionStack.isEmpty()) throw new ProgramException("The execution stack of the program is empty");

        StatementInterface nextStatement = executionStack.pop();
        return nextStatement.execute(this);
    }

    public int getProgramId(){
        return programId;
    }

    public MyStack<StatementInterface> exeStack() {
        return exeStack;
    }

    public MyMap<String, Value> symTable() {
        return symTable;
    }

    public MyList<Value> out() {
        return out;
    }

    public MyMap<StringValue, BufferedReader> fileTable() {
        return fileTable;
    }

    public MyHeap heapTable() {
        return heapTable;
    }
}

