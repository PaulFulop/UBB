package model.statements;

import exceptions.MyException;
import exceptions.TypecheckException;
import model.states.MyMap;
import model.states.ProgramState;
import model.types.Type;

public record CompoundStatement(StatementInterface first, StatementInterface second) implements StatementInterface {

    public ProgramState execute(ProgramState state) {
        var exeStack = state.exeStack();
        exeStack.push(second);
        exeStack.push(first);
        return null;
    }

    @Override
    public MyMap<String, Type> typecheck(MyMap<String, Type> typeTable) throws TypecheckException {
        return second.typecheck(first.typecheck(typeTable));
    }

    @Override
    public String toString() {
        return "(" + first.toString() + ";" + second.toString() + ")";
    }
}
