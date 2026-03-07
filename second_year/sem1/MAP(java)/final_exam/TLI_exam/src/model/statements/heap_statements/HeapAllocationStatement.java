package model.statements.heap_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.expressions.Expression;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.RefType;
import model.types.Type;
import model.values.RefValue;

public record HeapAllocationStatement(String name, Expression expression) implements StatementInterface {


    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        var symTable = state.symTable();
        var heapTable = state.heapTable();
        var tableValue = symTable.lookup(name);
        if (!(tableValue.getType() instanceof RefType)) throw new StatementException("Invalid sym table entry");

        var innerReferenceType = ((RefType)tableValue.getType()).getInnerType(); // type inside the reference
        var expressionValue = expression.evaluate(symTable, heapTable);

        if(!(expressionValue.getType().equals(innerReferenceType)))
            throw new StatementException("The type of the expression ( " + expressionValue.getType() + " ) does not match the type of the table entry ( " + innerReferenceType + " )");


        int addressLocation = heapTable.add(expressionValue);
        symTable.update(name, new RefValue(addressLocation, innerReferenceType));

        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        Type typeVariable = typeTable.lookup(name);
        Type typeExpression = expression.typecheck(typeTable);
        if (typeVariable.equals(new RefType(typeExpression)))
            return typeTable;
        else
            throw new TypecheckException("HeapAllocationStatement: right hand side and left hand side have different types ");
    }

    @Override
    public String toString() {
        return "new (" + name + "," + expression.toString() + ")";
    }
}
