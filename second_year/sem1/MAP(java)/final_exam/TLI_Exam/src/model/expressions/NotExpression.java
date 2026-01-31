package model.expressions;

import exceptions.ExpressionEvalException;
import exceptions.TypecheckException;
import model.states.MyHeap;
import model.states.MyMap;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;
import model.values.Value;

public record NotExpression(Expression expression) implements Expression {
    @Override
    public Value evaluate(MyMap<String, Value> symTable, MyHeap heapTable) throws ExpressionEvalException {
        Value value = expression.evaluate(symTable, heapTable);
        return new BoolValue(!((BoolValue) value).val());
    }

    @Override
    public Type typecheck(MyMap<String, Type> typeTable) throws TypecheckException {
        Type expressionType = expression.typecheck(typeTable);

        if(expressionType.equals(BoolType.INSTANCE))
            return BoolType.INSTANCE;

        throw new TypecheckException("Invalid expression type");
    }

    @Override
    public String toString() {
        return "not (" + expression.toString() + ")";
    }
}
