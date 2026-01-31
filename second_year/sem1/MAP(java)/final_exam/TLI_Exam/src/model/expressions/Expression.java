package model.expressions;


import exceptions.ExpressionEvalException;
import exceptions.TypecheckException;
import model.states.MyHeap;
import model.states.MyMap;
import model.types.Type;
import model.values.Value;

public interface Expression {
    Value evaluate(MyMap<String, Value> symTable, MyHeap heapTable) throws ExpressionEvalException;
    Type typecheck(MyMap<String, Type> typeTable) throws TypecheckException;
}

