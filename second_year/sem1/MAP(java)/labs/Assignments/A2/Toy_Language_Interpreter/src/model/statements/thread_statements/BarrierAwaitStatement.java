package model.statements.thread_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;

import java.util.List;

public record BarrierAwaitStatement(String variableName) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
            // - foundIndex=lookup(SymTable,var). If var is not in SymTable or has not the int
            //type print an error message and terminate the execution.
            //- if foundIndex is not an index in the BarrierTable then
            // print an error message and terminate the execution
            // else
            // - retrieve the entry for that foundIndex, as BarrierTable[foundIndex]== (N1,List1)
            // - compute the length of that list List1 as NL=length(L1)
            //- if (N1>NL) then
            // if(the identifier of the current PrgState is in L1) then
            //- push back await(var) on the ExeStack
            // else
            //- add the id of the current PrgState to L1
            //- push back await(var) on the ExeStack
            // else
            // do nothing

            var foundIndex = state.symTable().lookup(variableName);
            if(foundIndex instanceof IntValue(int val)){ // pattern matching
                var barrierEntry = state.barrierTable().lookup(val);
                List<Integer> L1 = barrierEntry.getValue();
                int NL = L1.size(), N1 = barrierEntry.getKey();

                if (N1 > NL){
                    if(L1.contains(N1)){
                        state.exeStack().push(this);
                    }
                    else {
                        L1.add(state.getProgramId());
                        state.exeStack().push(this);
                    }
                }
            }
            else
                throw new StatementException("Variable " + variableName + " is not a Int type");

            return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        Type variableType = typeTable.lookup(variableName);
        if(!(variableType instanceof IntType))
            throw new TypecheckException("Variable " + variableName + " is not a Int type");

        return typeTable;
    }
}
