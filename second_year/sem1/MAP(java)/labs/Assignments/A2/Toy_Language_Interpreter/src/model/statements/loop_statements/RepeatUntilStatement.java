package model.statements.loop_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.expressions.Expression;
import model.expressions.NotExpression;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.BoolType;
import model.types.Type;

public record RepeatUntilStatement (StatementInterface statement, Expression expression) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        state.exeStack().push(new WhileStatement(new NotExpression(expression), statement));
        state.exeStack().push(statement);

        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        // here if I don't clone the type table, the declarations inside the while body will "leak"
        // into the main program

        Type typeExpression = expression.typecheck(typeTable);
        if (!typeExpression.equals(BoolType.INSTANCE)) {
            throw new TypecheckException("RepeatUntilStatement: Until condition must be bool type");
        }

        statement.typecheck(typeTable.deepcopy());
        return typeTable;
    }

    @Override
    public String toString() {
        return "repeat (" + statement.toString() + ") until (" + expression.toString() + ')';
    }
}
