package model.statements.thread_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import javafx.util.Pair;
import model.expressions.Expression;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.IntType;
import model.types.Type;
import model.values.IntValue;
import java.util.ArrayList;

public record NewBarrierStatement(String variableName, Expression expression) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        //- evaluate the expression exp using SymTable1 and Heap1 and the
        //evaluation result must be an integer . If it is not an integer then print an
        //error and stop the execution. Let be Nr the result of this evaluation.
        //BarrierTable2 = BarrierTable1 synchronizedUnion
        // {newfreelocation ->(Nr,empty list)}
        //if var exists in SymTable1 and var has the type int then
        //SymTable2 = update(SymTable1,var, newfreelocation)
        // else print an error and stop the execution

        var num = expression.evaluate(state.symTable(), state.heapTable());
        if(num.getType() instanceof IntType){
            int location = state.barrierTable().add(new Pair<>(((IntValue) num).val(), new ArrayList<>()));

            var variableValue = state.symTable().lookup(variableName);
            if (variableValue.getType() instanceof IntType) {
                state.symTable().update(variableName, new IntValue(location));
            }
            else{
                throw new StatementException("BarrierTable: the variable is not of type int");
            }
        }
        else{
            throw new StatementException("Barrier: Invalid expression");
        }

        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        Type variableType = typeTable.lookup(variableName);
        Type expressionType = expression.typecheck(typeTable);

        if(!(variableType instanceof IntType &&  expressionType instanceof IntType))
            throw new TypecheckException("Variable and expression type not of type IntType");
        return typeTable;
    }
}
