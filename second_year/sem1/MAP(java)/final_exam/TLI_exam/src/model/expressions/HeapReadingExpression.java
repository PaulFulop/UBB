package model.expressions;

import exceptions.ExpressionEvalException;
import exceptions.TypecheckException;
import model.states.map.tables.HeapTable;
import model.states.map.tables.SymbolTable;
import model.states.map.tables.TypeTable;
import model.types.RefType;
import model.types.Type;
import model.values.RefValue;
import model.values.Value;

public record HeapReadingExpression(Expression expression) implements Expression {
    @Override
    public Value evaluate(SymbolTable symTable, HeapTable heapTable) throws ExpressionEvalException {
        var expressionValue = expression.evaluate(symTable, heapTable);
        if (!(expressionValue instanceof RefValue)) throw new ExpressionEvalException("The expression value does not match");

        int address = ((RefValue) expressionValue).address();
        return heapTable.lookup(address);
    }

    @Override
    public Type typecheck(TypeTable typeTable) throws TypecheckException {
        Type type = expression.typecheck(typeTable);
        if (type instanceof RefType) {
            return ((RefType) type).getInnerType();
        } else
            throw new TypecheckException("the HeapReadingExpression argument is not a RefType");
    }

    @Override
    public String toString() {
        return expression.toString();
    }
}
