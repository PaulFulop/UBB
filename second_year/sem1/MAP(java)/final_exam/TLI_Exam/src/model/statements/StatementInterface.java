package model.statements;

import exceptions.StatementException;
import exceptions.TypecheckException;
import model.states.MyMap;
import model.states.ProgramState;
import model.types.Type;

public interface StatementInterface {
    ProgramState execute(ProgramState state) throws StatementException;
    MyMap<String, Type> typecheck(MyMap<String, Type> typeTable) throws TypecheckException;
}
