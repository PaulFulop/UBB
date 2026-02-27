package model.statements.thread_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.IntType;
import model.values.IntValue;

import java.util.List;

public record AcquireStatement(String variableName) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        // pop the statement
        // - foundIndex=lookup(SymTable,var). If var is not in SymTable or has not the type
        //int then print an error message and terminate the execution.
        // - if foundIndex is not an index in the SemaphoreTable then
        //print an error message and terminate the execution
        // else
        // - retrieve the entry for that foundIndex, as SemaphoreTable[foundIndex]==
        //(N1,List1)
        //- compute the length of that list List1 as NL=length(List1)
        //- if (N1>NL) then
        // if(the identifier of the current PrgState is in List1) then
        // - do nothing
        // else
        // - add the id of the current PrgState to List1
        // else
        // - push back acquire(var) on the ExeStack

        var index = state.symTable().lookup(variableName);
        if(index instanceof IntValue(int foundIndex)){
            var semaphoreEntry = state.semaphoreTable().lookup(foundIndex);
            List<Integer> L1 = semaphoreEntry.getValue();
            int NL = L1.size(), N1 = semaphoreEntry.getKey();

            if (N1 > NL){
                if(!L1.contains(N1))
                    L1.add(state.getProgramId());
            }
            else
                state.exeStack().push(this);
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
