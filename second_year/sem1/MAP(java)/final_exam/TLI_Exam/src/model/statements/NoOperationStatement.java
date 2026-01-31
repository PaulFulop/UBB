package model.statements;

import exceptions.TypecheckException;
import model.states.MyMap;
import model.states.ProgramState;
import model.types.Type;

public class NoOperationStatement implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }

    @Override
    public MyMap<String, Type> typecheck(MyMap<String, Type> typeTable) throws TypecheckException {
        return typeTable;
    }

    @Override
    public String toString() {
        return "NOP";
    }
}

