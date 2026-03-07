package model.statements.basic_statements;

import exceptions.TypecheckException;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.*;

public record VariableDeclarationStatement(String name, Type type) implements StatementInterface {

    @Override
    public ProgramState execute(ProgramState state) {
        var symTable = state.symTable();
        symTable.add(name, type.getDefaultValue());
        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        typeTable.add(name, type);
        return typeTable;
    }

    @Override
    public String toString() {
        return type.toString() + ' ' + name;
    }
}
