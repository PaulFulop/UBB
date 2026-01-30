package model.statements;

import exceptions.ExpressionEvalException;
import exceptions.StatementException;
import exceptions.TypecheckException;
import model.expressions.Expression;
import model.states.MyMap;
import model.states.ProgramState;
import model.types.RefType;
import model.types.Type;
import model.values.IntValue;
import model.values.RefValue;

public record HeapWritingStatement(String name, Expression expression) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        var symTable = state.symTable();
        var heapTable = state.heapTable();
        var tableValue = symTable.lookup(name);

        if(!(tableValue.getType() instanceof RefType)) throw new ExpressionEvalException("The type of the value inside the symbol table is not a reference type.");

        int address = ((RefValue)tableValue).address();
        if (!heapTable.isDefined(new IntValue(address))) throw new ExpressionEvalException("The address of the value inside the heap table is not defined.");

        var expressionValue = expression.evaluate(symTable, heapTable);

        if (!(expressionValue.getType().equals(((RefType) tableValue.getType()).getInnerType()))){
            throw new ExpressionEvalException("The type of the value inside the symbol table is equal with the type of the expression.");
        }


        heapTable.update(new IntValue(address), expressionValue);
        return null;
    }

    @Override
    public MyMap<String, Type> typecheck(MyMap<String, Type> typeTable) throws TypecheckException {
        Type typeVariable = typeTable.lookup(name);
        Type typeExpression = expression.typecheck(typeTable);
        if (typeVariable.equals(new RefType(typeExpression)))
            return typeTable;
        else
            throw new TypecheckException("HeapWritingStatement: right hand side and left hand side have different types ");
    }
}
