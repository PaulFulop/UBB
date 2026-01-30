package model.statements;

import exceptions.DefinedIdException;
import exceptions.MyException;
import exceptions.TypecheckException;
import model.states.MyMap;
import model.states.ProgramState;
import model.types.*;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.RefValue;
import model.values.Value;

public record VariableDeclarationStatement(String name, Type type) implements StatementInterface {

    @Override
    public ProgramState execute(ProgramState state) {
        var symTable = state.symTable();
        symTable.add(name, type.getDefaultValue());
        return null;
    }

    @Override
    public MyMap<String, Type> typecheck(MyMap<String, Type> typeTable) throws TypecheckException {
        typeTable.add(name, type);
        return typeTable;
    }

    @Override
    public String toString() {
        return type.toString() + ' ' + name;
    }
}
