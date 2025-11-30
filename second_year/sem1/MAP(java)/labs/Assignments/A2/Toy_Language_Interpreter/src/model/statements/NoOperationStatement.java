package model.statements;

import model.states.ProgramState;

public class NoOperationStatement implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }

    @Override
    public String toString() {
        return "NOP";
    }
}

