package model.statements.thread_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.IntType;
import model.values.IntValue;

public record NewLockStatement(String variableName) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        //LockTable2 = LockTable1 synchronizedUnion {newfreelocation ->-1}
        //if var exists in SymTable1 and has the type int then
        // SymTable2 = update(SymTable1,var, newfreelocation)
        var num = state.symTable().lookup(variableName);

        if(num.getType() instanceof IntType) {
            int location = state.lockTable().add(-1);
            state.symTable().update(variableName, new IntValue(location));
        }
        else
            throw new StatementException("Variable " + variableName + " is not a int");

        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        var valueType = typeTable.lookup(variableName);
        if(!(valueType instanceof IntType))
            throw new TypecheckException("Variable " + variableName + " is not a int");

        return typeTable;
    }
}
