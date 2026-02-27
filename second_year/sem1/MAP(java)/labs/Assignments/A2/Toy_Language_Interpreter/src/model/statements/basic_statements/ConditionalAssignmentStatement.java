package model.statements.basic_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.expressions.Expression;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.BoolType;

public record ConditionalAssignmentStatement(String variableName,
                                             Expression expression1,
                                             Expression expression2,
                                             Expression expression3) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        if (!state.symTable().isDefined(variableName)) throw  new StatementException("Missing variable");
        StatementInterface newStatement = new IfStatement(expression1,
                new AssignStatement(variableName, expression2),
                new AssignStatement(variableName, expression3));

        state.exeStack().push(newStatement);

        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        var expression1Type = expression1.typecheck(typeTable);
        var expression2Type = expression2.typecheck(typeTable);
        var expression3Type = expression3.typecheck(typeTable);
        var variableType = typeTable.lookup(variableName);

        if (!(expression1Type instanceof BoolType) || !(expression2Type.equals(expression3Type) &&
                                                        expression3Type.equals(variableType)))
            throw  new TypecheckException("Type mismatch");

        return typeTable;
    }

    @Override
    public String toString() {
        return variableName + "=" + expression1.toString() + "?" + expression2.toString() + ":" + expression3.toString();
    }
}
