package model.statements.basic_statements;

import exceptions.TypecheckException;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;

public class NoOperationStatement implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        return typeTable;
    }

    @Override
    public String toString() {
        return "NOP";
    }
}

