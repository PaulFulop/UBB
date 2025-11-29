package model.statements;

import exceptions.StatementException;
import model.states.ProgramState;

public interface StatementInterface {
    ProgramState execute(ProgramState state) throws StatementException;
}
