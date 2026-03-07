package model.statements.basic_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.expressions.Expression;
import model.states.map.tables.TypeTable;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;

public record IfStatement(Expression expression, StatementInterface thenS, StatementInterface elseS) implements StatementInterface {

    public ProgramState execute(ProgramState state) throws StatementException {
        var exeStack = state.exeStack();
        var cond = expression.evaluate(state.symTable(), state.heapTable());
        if (cond.getType() == BoolType.INSTANCE) {
            if (cond.equals(new BoolValue(true)))
                exeStack.push(thenS);
            else
                exeStack.push(elseS);
        } else throw new StatementException("Condition is not boolean");

        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {

        // WHY DO I NEED TO CLONE THE TYPE TABLE?
        // If thenS or elseS contain variable declarations:
        //if (x > 0) then
        //int temp = 5;  -> temp added to typeTable
        //else
        //string temp = "hi"; -> Different temp, should be in separate scope

        Type typeExpression = expression.typecheck(typeTable);
        if (typeExpression.equals(BoolType.INSTANCE)) {
            thenS.typecheck(typeTable.deepcopy());
            elseS.typecheck(typeTable.deepcopy());
            return typeTable;
        }
        else
            throw new TypecheckException("The condition of IF has not the type bool");
    }

    @Override
    public String toString() {
        return "IF (" + expression.toString() + ") THEN (" + thenS.toString() + ") ELSE (" + elseS.toString() + ")";
    }
}
