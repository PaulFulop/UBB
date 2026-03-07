package model.expressions;

import exceptions.ExpressionEvalException;
import exceptions.TypecheckException;
import model.states.map.tables.HeapTable;
import model.states.map.tables.SymbolTable;
import model.states.map.tables.TypeTable;
import model.types.BoolType;
import model.types.IntType;
import model.types.Type;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.Value;

public record RelationalExpression(String op, Expression e1, Expression e2) implements Expression {
    public Value evaluate(SymbolTable symTable, HeapTable heapTable) throws ExpressionEvalException {
        Value v1, v2;
        v1 = e1.evaluate(symTable, heapTable);
        v2 = e2.evaluate(symTable, heapTable);

        IntValue i1 = (IntValue) v1;
        IntValue i2 = (IntValue) v2;
        int n1, n2;
        n1 = i1.val();
        n2 = i2.val();

        return switch (op) {
            case "<" -> new BoolValue(n1 < n2);
            case "<=" -> new BoolValue(n1 <= n2);
            case "==" -> new BoolValue(n1 == n2);
            case "!=" -> new BoolValue(n1 != n2);
            case ">=" -> new BoolValue(n1 >= n2);
            case ">" -> new BoolValue(n1 > n2);
            default -> throw new ExpressionEvalException("RelationalExpression: invalid operation");
        };
    }

    @Override
    public Type typecheck(TypeTable typeTable) throws TypecheckException {
        Type type1, type2;
        type1=e1.typecheck(typeTable);
        type2=e2.typecheck(typeTable);

        if (type1.equals(IntType.INSTANCE)){
            if (type2.equals(IntType.INSTANCE)) {
                return BoolType.INSTANCE;
            }
            else
                throw new TypecheckException("second operand is not an integer");
        }
        else
            throw new TypecheckException("first operand is not an integer");
    }

    @Override
    public String toString() {
        return e1.toString() + ' ' + op + ' ' + e2.toString();
    }
}

