package model.statements.thread_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.IntType;
import model.values.IntValue;

public record LatchAwaitStatement(String variableName) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        //- pop the statement
        // - foundIndex=lookup(SymTable,var). If var is not in SymTable or it has not the
        //type int then print an error message and terminate the execution.
        // - if foundIndex is not an index in the LatchTable then
        //print an error message and terminate the execution
        // elseif LatchTable[foundIndex]==0 then
        // do nothing
        //else push back the await statement(that means the current PrgState must wait for the
        //countdownlatch to reach zero)

        var index = state.symTable().lookup(variableName);
        if(index instanceof IntValue(int foundIndex)){
            Integer latchTableValue = state.latchTable().lookup(foundIndex);
            if(latchTableValue != 0)
                state.exeStack().push(this);
        }

        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        var variableType = typeTable.lookup(variableName);
        if(!(variableType instanceof IntType))
            throw new TypecheckException("Variable " + variableName + " is not of type IntType");
        return typeTable;
    }
}
