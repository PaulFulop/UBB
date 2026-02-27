package model.statements.loop_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;

import model.expressions.Expression;
import model.expressions.RelationalExpression;
import model.expressions.VariableExpression;
import model.statements.StatementInterface;
import model.statements.basic_statements.AssignStatement;
import model.statements.basic_statements.CompoundStatement;
import model.statements.basic_statements.VariableDeclarationStatement;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.IntType;
import model.types.Type;

public record ForStatement(String variableName, Expression expression1, Expression expression2,
                           Expression expression3, StatementInterface statement) implements StatementInterface {

    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        if (state.symTable().isDefined(variableName))
            throw new  StatementException("The variable " + variableName + " is already defined");

        StatementInterface newStatement =
                new CompoundStatement(new VariableDeclarationStatement(variableName, IntType.INSTANCE),
                        new CompoundStatement(
                                new AssignStatement(variableName, expression1),
                                new WhileStatement(
                                        new RelationalExpression("<",
                                                new VariableExpression(variableName), expression2),
                                        new CompoundStatement(statement, new AssignStatement(variableName, expression3)))
                        ));

        state.exeStack().push(newStatement);

        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        Type typeExpression1 = expression1.typecheck(typeTable);
        Type typeExpression2 = expression2.typecheck(typeTable);

        //PROBLEM in expression3 because it's an assign statement on v that depends on v but we typecheck
        // before we run the program, and we don't have x
        // and if we also use v inside the for loop then we ll get an error again from below =>
        // I have to add this manually since typechecking happens before I run
        // the program and actually create the variable.
        typeTable.add(variableName, IntType.INSTANCE); // for a TLI I will always consider that the value
                                                        // that im iterating over is an integer
                                                        // (actually for all the loop implementations in general I guess,
                                                        // because my relational expression only accepts Int values for now)

        Type typeExpression3 = expression3.typecheck(typeTable);
        if (!(typeExpression1 instanceof IntType) || !(typeExpression2 instanceof IntType || !(typeExpression3 instanceof IntType)) ) {
            throw new TypecheckException("ForStatement: expressions inside for loop must be integers");
        }


        // here if I don't clone the type table, the declarations inside the while body will "leak"
        // into the main program
        statement.typecheck(typeTable.deepcopy());

        typeTable.remove(variableName); // removing the temporary entry
        return typeTable;
    }

    @Override
    public String toString() {
        return "for(" + variableName + "=" + expression1.toString() + ";" + variableName + "<" + expression2.toString() + ";" + variableName + "=" + expression3.toString() + ")(" + statement.toString() + ")";
    }

}
