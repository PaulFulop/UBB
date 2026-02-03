package model.statements.basic_statements;

import exceptions.TypecheckException;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.expressions.Expression;
import model.states.map.tables.TypeTable;

public record PrintStatement(Expression expression) implements StatementInterface {

    public ProgramState execute(ProgramState state) {
        var out = state.out();
        out.add(expression.evaluate(state.symTable(), state.heapTable()));

        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        expression.typecheck(typeTable);
        return typeTable;
    }

    @Override
    public String toString() {
        return "print(" + expression.toString() + ")";
    }
}
