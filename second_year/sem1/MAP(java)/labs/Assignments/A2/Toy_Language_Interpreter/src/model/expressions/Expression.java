package model.expressions;


import exceptions.ExpressionEvalException;
import model.states.HeapInterface;
import model.states.SymbolTableInterface;
import model.values.Value;

public interface Expression {
    Value evaluate(SymbolTableInterface symTable, HeapInterface heapTable) throws ExpressionEvalException;
}

