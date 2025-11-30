package model.statements;

import exceptions.ExpressionEvalException;
import exceptions.StatementException;
import model.expressions.Expression;
import model.states.Heap;
import model.states.ProgramState;
import model.states.SymbolTableInterface;
import model.types.RefType;
import model.values.RefValue;
import model.values.Value;

import java.sql.Statement;

public record HeapWritingStatement(String name, Expression expression) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        var symTable = state.symTable();
        var heapTable = state.heapTable();
        var tableValue = symTable.lookup(name);

        if(!(tableValue.getType() instanceof RefType)) throw new ExpressionEvalException("The type of the value inside the symbol table is not a reference type.");

        int address = ((RefValue)tableValue).address();
        if (!heapTable.isDefined(address)) throw new ExpressionEvalException("The address of the value inside the heap table is not defined.");

        var expressionValue = expression.evaluate(symTable, heapTable);

        if (!(expressionValue.getType().equals(((RefType) tableValue.getType()).getInnerType()))){
            throw new ExpressionEvalException("The type of the value inside the symbol table is equal with the type of the expression.");
        }


        heapTable.update(address, expressionValue);
        return null;
    }
}
