package model.statements.file_statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.expressions.Expression;
import model.statements.StatementInterface;
import model.states.ProgramState;
import model.states.map.tables.TypeTable;
import model.types.StringType;
import model.types.Type;
import model.values.StringValue;

import java.io.BufferedReader;
import java.io.FileReader;

public record OpenFileStatement(Expression expression) implements StatementInterface {
    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        var symbolTable = state.symTable();
        var fileTable = state.fileTable();
        var heapTable = state.heapTable();
        var exp = expression.evaluate(symbolTable, heapTable);

        if (exp.getType() != StringType.INSTANCE) {
            throw new StatementException("Expected a string, got " + exp.getType());
        }

        var expStr = ((StringValue) exp).val();

        try {
            var bufferedReader = new BufferedReader(new FileReader(expStr));
            fileTable.add((StringValue) exp, bufferedReader);
        }
        catch (Exception e) {
            throw new StatementException(e.getMessage());
        }

        return null;
    }

    @Override
    public TypeTable typecheck(TypeTable typeTable) throws TypecheckException {
        Type typeExpression = expression.typecheck(typeTable);

        if (typeExpression instanceof StringType)
            return typeTable;

        throw new TypecheckException("OpenFileStatemen: error opening file, type of expression was not correct");
    }

    @Override
    public String toString() {
        return "open (" + expression.toString() + ')';
    }
}
