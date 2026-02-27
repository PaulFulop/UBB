package model.statements.thread_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.IntType;
import model.values.IntValue;

import java.util.List;

public record RelaseStatement(String variableName) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        //- pop the statement
        // - foundIndex=lookup(SymTable,var). If var is not in SymTable or has not int type
        //then print an error message and terminate the execution.
        // - if foundIndex is not an index in the SemaphoreTable then
        //print an error message and terminate the execution
        // else
        // - retrieve the entry for that foundIndex, as SemaphoreTable[foundIndex]==
        //(N1,List1)
        // - if(the identifier of the current PrgState is in List1) then
        // - remove the identifier of the current PrgState from List1
        // else
        // - do nothing
        var index = state.symTable().lookup(variableName);
        if(index instanceof IntValue(int foundIndex)){
            var barrierEntry = state.semaphoreTable().lookup(foundIndex);
            List<Integer> L1 = barrierEntry.getValue();

            if (L1.contains(state.getProgramId()))
                //state.semaphoreTable().lookup(foundIndex).getValue().remove(state.getProgramId());
                L1.remove(Integer.valueOf(state.getProgramId())); // otherwise it removes from
                                                                    // position since int is primitive
        }
        else
            throw new StatementException("Variable " + variableName + " is not a Int type");

        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        var variableType = typeTable.lookup(variableName);
        if(!(variableType instanceof IntType))
            throw new TypecheckException("Variable " + variableName + " is not an integer");
        return typeTable;
    }
}
