package model.statements;

import exceptions.TypecheckException;
import model.states.MyMap;
import model.states.ProgramState;
import model.expressions.Expression;
import exceptions.MyException;
import model.types.Type;

public record PrintStatement(Expression expression) implements StatementInterface {

    public ProgramState execute(ProgramState state) {
        var out = state.out();
        out.add(expression.evaluate(state.symTable(), state.heapTable()));

        return null;
    }

    @Override
    public MyMap<String, Type> typecheck(MyMap<String, Type> typeTable) throws TypecheckException {
        expression.typecheck(typeTable);
        return typeTable;
    }

    @Override
    public String toString() {
        return "print(" + expression.toString() + ")";
    }
}
