package model.statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;

public interface StatementInterface {
    ProgramState execute(ProgramState state) throws StatementException;
    TypeTable typecheck(TypeTable typeTable) throws TypecheckException;
}
