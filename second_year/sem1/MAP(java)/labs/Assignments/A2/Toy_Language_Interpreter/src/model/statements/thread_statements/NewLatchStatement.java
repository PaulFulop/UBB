package model.statements.thread_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.expressions.Expression;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.IntType;
import model.values.IntValue;

public record NewLatchStatement(String variableName, Expression expression) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        //- evaluate the expression using SymTable and Heap and let be num the result
        //of this evaluation. If num is not an integer then print an error and stop the execution.
        //LatchTable2 = LatchTable1 synchronizedUnion {newfreelocation ->num1}
        //if var exists in SymTable1 and has the type int then
        //SymTable2 = update(SymTable1,var, newfreelocation)
        //else print an error and stop the execution.

        var num = expression.evaluate(state.symTable(), state.heapTable());
        if(num instanceof IntValue(int val)){
            int location = state.latchTable().add(val);

            var variableValue = state.symTable().lookup(variableName);
            if(variableValue.getType() instanceof IntType){
                state.symTable().update(variableName, new IntValue(location));
            }
            else throw new StatementException("Variable " + variableName + " is not a int");
        }
        else throw new StatementException("Wrong type of expression");
        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        var variableType = typeTable.lookup(variableName);
        var expressionType = expression.typecheck(typeTable);

        if(!(variableType instanceof IntType) || !(expressionType instanceof IntType))
            throw new TypecheckException("Wrong type of expression or variable");

        return typeTable;
    }
}
