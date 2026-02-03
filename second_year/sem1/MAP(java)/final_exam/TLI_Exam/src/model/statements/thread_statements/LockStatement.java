package model.statements.thread_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.IntType;
import model.values.IntValue;

public record LockStatement(String variableName) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        //- pop the statement
        // - foundIndex=lookup(SymTable,var). If var is not in SymTable or has not int type
        //then print an error message and terminate the execution.
        // - if foundIndex is not an index in the LockTable then
        // print an error message and terminate the execution
        // elseif LockTable[foundIndex]==-1 then
        // LockTable[foundIndex]=Identifier of the PrgState
        // else push back the lock statement(that means other PrgState holds the lock)

        var index = state.symTable().lookup(variableName);
        if(index instanceof IntValue(int foundIndex)){
            if(!(state.lockTable().isDefined(foundIndex)))
                throw new StatementException("Variable " + variableName + " is not defined inside the lock table");

            int lockTableValue = state.lockTable().lookup(foundIndex);
            if(lockTableValue == -1)
                state.lockTable().update(foundIndex, state.getProgramId());
            else
                state.exeStack().push(this); // it's like we go into a loop until we unlock
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
