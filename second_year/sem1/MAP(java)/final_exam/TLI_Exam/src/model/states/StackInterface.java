package model.states;

import model.statements.StatementInterface;
import java.util.EmptyStackException;

public interface StackInterface<T> {
    T pop() throws EmptyStackException;
    T get(int index) throws EmptyStackException;
    int size();
    void push(T v);
    boolean isEmpty();

}

