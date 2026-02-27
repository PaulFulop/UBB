package model.statements.basic_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.expressions.Expression;
import model.expressions.RelationalExpression;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;

public record SwitchCaseStatement(Expression switchExpression,
                                  Expression expression1,
                                  Expression expression2,
                                  StatementInterface statement1,
                                  StatementInterface statement2,
                                  StatementInterface statement3) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        //if(exp==exp1) then stmt1 else (if (exp==exp2) then stmt2 else stmt3)
        StatementInterface newStatement =
                new IfStatement(new RelationalExpression("==", switchExpression, expression1),
                        statement1,
                        new IfStatement(
                                new RelationalExpression("==",
                                        switchExpression, expression2), statement2, statement3));
        state.exeStack().push(newStatement);
        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        statement1.typecheck(typeTable.deepcopy());
        statement2.typecheck(typeTable.deepcopy());
        statement3.typecheck(typeTable.deepcopy());

        var switchExp = switchExpression.typecheck(typeTable);
        var exp1Type = expression1.typecheck(typeTable);
        var exp2Type = expression2.typecheck(typeTable);
        if(!(switchExp.equals(exp1Type) && switchExp.equals(exp2Type)))
            throw new TypecheckException("Type mismatch");
        return typeTable;
    }

    @Override
    public String toString(){
        return "switch("+switchExpression.toString()+") case("+expression1.toString()+
                ":"+statement1.toString()+") case("+expression2.toString()+
                ":"+statement2.toString()+") (default "+statement3.toString();
    }
}
