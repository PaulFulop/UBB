package model.expressions;

import exceptions.ExpressionEvalException;
import exceptions.TypecheckException;
import model.states.map.tables.HeapTable;
import model.states.map.tables.SymbolTable;
import model.states.map.tables.TypeTable;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;
import model.values.Value;

public record NotExpression(Expression expression) implements Expression {
    @Override
    public Value evaluate(SymbolTable symTable, HeapTable heapTable) throws ExpressionEvalException {
        Value value = expression.evaluate(symTable, heapTable);
        return new BoolValue(!((BoolValue) value).val());
    }

    @Override
    public Type typecheck(TypeTable typeTable) throws TypecheckException {
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
