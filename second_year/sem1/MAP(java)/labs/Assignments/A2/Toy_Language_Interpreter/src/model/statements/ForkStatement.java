package model.statements;

import exceptions.StatementException;
import model.states.*;

import javax.print.attribute.standard.Copies;

public record ForkStatement(StatementInterface statement) implements StatementInterface {

    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        var executionStack = new LinkedListExecutionStack();
        executionStack.push(statement);

        return new ProgramState(
                executionStack,
                new MapSymbolTable(state.symTable().getMap()), // -> a copy of it, not reference
                state.out(),
                state.fileTable(),
                state.heapTable());
    }

    @Override
    public String toString() {
        return "fork( " + statement.toString() + " )";
    }
}
