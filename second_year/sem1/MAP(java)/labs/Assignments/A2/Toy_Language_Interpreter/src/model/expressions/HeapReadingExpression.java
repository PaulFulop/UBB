package model.expressions;

import exceptions.ExpressionEvalException;
import model.states.Heap;
import model.states.HeapInterface;
import model.states.SymbolTableInterface;
import model.values.RefValue;
import model.values.Value;

public record HeapReadingExpression(Expression expression) implements Expression {
    @Override
    public Value evaluate(SymbolTableInterface symTable, HeapInterface heapTable) throws ExpressionEvalException {
        var expressionValue = expression.evaluate(symTable, heapTable);
        if (!(expressionValue instanceof RefValue)) throw new ExpressionEvalException("The expression value does not match");

        int address = ((RefValue) expressionValue).address();
        return heapTable.lookup(address);
    }

    @Override
    public String toString() {
        return expression.toString();
    }
}
