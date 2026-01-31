package model.statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.states.MyMap;
import model.states.ProgramState;
import model.expressions.Expression;
import exceptions.MyException;
import model.types.BoolType;
import model.types.Type;
import model.values.BoolValue;

import java.util.Map;

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
    public MyMap<String, Type> typecheck(MyMap<String, Type> typeTable) throws TypecheckException {

        // WHY DO I NEED TO CLONE THE TYPE TABLE?
        // If thenS or elseS contain variable declarations:
        //if (x > 0) then
        //int temp = 5;  -> temp added to typeTable
        //else
        //string temp = "hi"; -> Different temp, should be in separate scope

        Type typeExpression = expression.typecheck(typeTable);
        if (typeExpression.equals(BoolType.INSTANCE)) {
            thenS.typecheck(new MyMap<>(typeTable.getMap()));
            elseS.typecheck(new MyMap<>(typeTable.getMap()));
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
