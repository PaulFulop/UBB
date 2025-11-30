package model.statements;

import exceptions.MyException;
import model.states.ProgramState;

public record CompoundStatement(StatementInterface first, StatementInterface second) implements StatementInterface {

    public ProgramState execute(ProgramState state) {
        var exeStack = state.exeStack();
        exeStack.push(second);
        exeStack.push(first);
        return null;
    }

    @Override
    public String toString() {
        return "(" + first.toString() + ";" + second.toString() + ")";
    }
}
