package model.statements;

import model.states.ProgramState;
import model.expressions.Expression;
import exceptions.MyException;

public record PrintStatement(Expression expression) implements StatementInterface {

    public ProgramState execute(ProgramState state) {
        var out = state.out();
        out.add(expression.evaluate(state.symTable(), state.heapTable()));

        return null;
    }

    @Override
    public String toString() {
        return "print(" + expression.toString() + ")";
    }
}
