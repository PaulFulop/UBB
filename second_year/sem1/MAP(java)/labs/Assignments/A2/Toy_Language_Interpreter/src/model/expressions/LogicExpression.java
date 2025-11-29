package model.expressions;

import exceptions.ExpressionEvalException;
import exceptions.MyException;
import model.states.Heap;
import model.states.HeapInterface;
import model.states.SymbolTableInterface;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.Value;

public record LogicExpression(String op, Expression e1, Expression e2) implements Expression {

    public Value evaluate(SymbolTableInterface symTable, HeapInterface heapTable) throws ExpressionEvalException {
        Value v1, v2;
        v1 = e1.evaluate(symTable, heapTable);
        v2 = e2.evaluate(symTable, heapTable);

        if (!v1.getType().equals(BoolType.INSTANCE) || !v2.getType().equals(BoolType.INSTANCE)) {
            throw new ExpressionEvalException("LogicExpression: invalid operation");
        }

        BoolValue b1 = (BoolValue) v1;
        BoolValue b2 = (BoolValue) v2;
        boolean n1, n2;
        n1 = b1.val();
        n2 = b2.val();

        return switch (op) {
            case "&&" -> new BoolValue(n1 && n2);
            case "||" -> new BoolValue(n1 || n2);
            default -> throw new ExpressionEvalException("LogicExpression: invalid operation");
        };
    }

    @Override
    public String toString() {
        return e1.toString() + ' ' + op + ' ' + e2.toString();
    }
}

