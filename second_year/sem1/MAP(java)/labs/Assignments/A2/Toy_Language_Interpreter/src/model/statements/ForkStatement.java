package model.statements;

import exceptions.StatementException;
import model.states.ProgramState;

public class ForkStatement implements StatementInterface {

    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        return null;
    }
}
