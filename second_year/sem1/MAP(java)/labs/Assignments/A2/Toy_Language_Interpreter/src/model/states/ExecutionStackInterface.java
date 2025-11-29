package model.states;

import model.statements.StatementInterface;
import java.util.EmptyStackException;

public interface ExecutionStackInterface{
    StatementInterface pop() throws EmptyStackException;
    void push(StatementInterface v);
    boolean isEmpty();
}

