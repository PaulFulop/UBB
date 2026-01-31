package model.expressions;

import exceptions.ExpressionEvalException;
import exceptions.TypecheckException;
import model.states.MyHeap;
import model.states.MyMap;
import model.types.Type;
import model.values.Value;

public record VariableExpression(String id) implements Expression {

    public Value evaluate(MyMap<String, Value> symTable, MyHeap heapTable) throws ExpressionEvalException {
        try{
            return symTable.lookup(id);
        }
        catch (Exception e){
            throw new ExpressionEvalException("VariableExpression: variable not found");
        }
    }

    @Override
    public Type typecheck(MyMap<String, Type> typeTable) throws TypecheckException {
        return typeTable.lookup(id);
    }

    @Override
    public String toString() {
        return id;
    }
}
