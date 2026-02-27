package model.statements.thread_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import javafx.util.Pair;
import model.expressions.Expression;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.IntType;
import model.values.IntValue;

import java.util.ArrayList;

public record NewSemaphoreStatement(String variableName, Expression expression) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        //- evaluate the expression using SymTable and Heap and let be num the
        //result of this evaluation. If num is not an integer then print an error and stop the
        //execution.
        //SemaphoreTable2 = SemaphoreTable1 synchronizedUnion {newfreelocation ->(number1,empty list)}
        //if var exists in SymTable1 and has the type int then
        //SymTable2 = update(SymTable1,var, newfreelocation)
        //else print an error and stop the execution.

        var num = expression.evaluate(state.symTable(), state.heapTable());
        if(num.getType() instanceof IntType){
            int location = state.semaphoreTable().add(new Pair<>(((IntValue) num).val(), new ArrayList<>()));

            var variableValue = state.symTable().lookup(variableName);
            if (variableValue.getType() instanceof IntType) {
                state.symTable().update(variableName, new IntValue(location));
            }
            else{
                throw new StatementException("SemaphoreTable: the variable is not of type int");
            }
        }
        else{
            throw new StatementException("Semaphore: Invalid expression");
        }
        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        var expressionType = expression.typecheck(typeTable);
        var variableType = typeTable.lookup(variableName);

        if(!(variableType instanceof IntType) || !(expressionType instanceof IntType))
            throw new TypecheckException("Variable or expression type is not an integer");
        return typeTable;
    }
}
