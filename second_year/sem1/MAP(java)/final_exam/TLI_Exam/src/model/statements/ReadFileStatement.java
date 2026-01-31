package model.statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.expressions.Expression;
import model.states.MyMap;
import model.states.ProgramState;
import model.types.IntType;
import model.types.StringType;
import model.types.Type;
import model.values.IntValue;
import model.values.StringValue;

public record ReadFileStatement(Expression expression, String variableName) implements StatementInterface {

    @Override
    public ProgramState execute(ProgramState state) throws StatementException {
        var symbolTable = state.symTable();
        var heapTable = state.heapTable();
        var fileTable = state.fileTable();

        if (symbolTable.lookup(variableName).getType() != IntType.INSTANCE)
            throw new StatementException("Missing variable.");

        var exp = expression.evaluate(symbolTable, heapTable);
        if (exp.getType() != StringType.INSTANCE) {
            throw new StatementException("Expected a string, got " + exp.getType());
        }

        try {
            var bufferedReader = fileTable.lookup((StringValue) exp);
            var line =  bufferedReader.readLine();
            IntValue newValue = (IntValue) IntType.INSTANCE.getDefaultValue();
            if (line != null) {
                newValue = new IntValue(Integer.parseInt(line));
            }

            symbolTable.update(variableName, newValue);
        }
        catch(Exception e){
            throw new StatementException(e.getMessage());
        }

        return null;
    }

    @Override
    public MyMap<String, Type> typecheck(MyMap<String, Type> typeTable) throws TypecheckException {
        Type typeExpression = expression.typecheck(typeTable);
        Type typeVariable = typeTable.lookup(variableName);

        if (typeExpression instanceof StringType && typeVariable instanceof IntType)
            return typeTable;

        throw new TypecheckException("ReadFileStatement: error reading file, the types were not correct");
    }

    @Override
    public String toString() {
        return "read (" + expression.toString() + ", " + variableName + ')';
    }
}
