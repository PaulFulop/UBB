package model.expressions;

import exceptions.ExpressionEvalException;
import exceptions.TypecheckException;
import model.states.map.tables.HeapTable;
import model.states.map.tables.SymbolTable;
import model.states.map.tables.TypeTable;
import model.types.Type;
import model.values.Value;

public record VariableExpression(String id) implements Expression {

    public Value evaluate(SymbolTable symTable, HeapTable heapTable) throws ExpressionEvalException {
        try{
            return symTable.lookup(id);
        }
        catch (Exception e){
            throw new ExpressionEvalException("VariableExpression: variable not found");
        }
    }

    @Override
    public Type typecheck(TypeTable typeTable) throws TypecheckException {
        return typeTable.lookup(id);
    }

    @Override
    public String toString() {
        return id;
    }
}
