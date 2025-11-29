package model.states;


import exceptions.ProgramException;
import model.statements.StatementInterface;

public record ProgramState(
        int programId, ExecutionStackInterface exeStack, SymbolTableInterface symTable, OutInterface out, FileTableInterface fileTable, Heap heapTable) {

    @Override
    public String toString() {
        return  "\n PROGRAM ID: " +  programId +
                "\nEXECUTION STACK:\n" + exeStack.toString() +
                "\nSYMBOL TABLE:\n" + symTable.toString() +
                "\nOUT:\n" + out.toString() +
                "\nFILE TABLE\n" + fileTable.toString() +
                "\nHEAP TABLE:\n" + heapTable.toString() +
                "\n\n";
    }

    public boolean isNotCompleted(){
        return !exeStack.isEmpty();
    }

    public ProgramState executeOneStep() throws ProgramException {
        ExecutionStackInterface executionStack = this.exeStack();
        if (executionStack.isEmpty()) throw new ProgramException("The execution stack of the program is empty");

        StatementInterface nextStatement = executionStack.pop();
        return nextStatement.execute(this);
    }
}

