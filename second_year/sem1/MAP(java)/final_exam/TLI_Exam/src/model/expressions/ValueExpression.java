package model.expressions;

import exceptions.TypecheckException;
import model.states.MyHeap;
import model.states.MyMap;
import model.types.Type;
import model.values.Value;

public record ValueExpression(Value e) implements Expression {

    public Value evaluate(MyMap<String, Value> symTable, MyHeap heapTable) {
        return e;
    }

    @Override
    public Type typecheck(MyMap<String, Type> typeTable) throws TypecheckException {
        return e.getType();
    }

    @Override
    public String toString() {
        return e.toString();
    }
}
