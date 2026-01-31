package model.statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.states.MyMap;
import model.states.ProgramState;
import model.expressions.Expression;
import exceptions.MyException;
import model.values.Value;
import model.types.Type;

public record AssignStatement(String name, Expression expression) implements StatementInterface {

    public ProgramState execute(ProgramState state) throws StatementException {
        var symTable = state.symTable();
        var heapTable = state.heapTable();

        var val = expression.evaluate(symTable, heapTable);
        Type typeId = (symTable.lookup(name)).getType();
        if (val.getType().equals(typeId))
            symTable.update(name, val);
        else
            throw new StatementException("declared type of variable " + name +
                    " and type of the assigned expression do not match");

        return null;
    }

    @Override
    public MyMap<String, Type> typecheck(MyMap<String, Type> typeTable) throws TypecheckException {
        Type typeVariable = typeTable.lookup(name);
        Type typeExpression = expression.typecheck(typeTable);
        if (typeVariable.equals(typeExpression))
            return typeTable;
        else
            throw new TypecheckException("Assignment: right hand side and left hand side have different types ");
    }

    @Override
    public String toString() {
        return name + " = " + expression.toString();
    }
}
