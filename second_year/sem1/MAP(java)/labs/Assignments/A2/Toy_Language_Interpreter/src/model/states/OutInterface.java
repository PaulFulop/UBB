package model.states;

import exceptions.EmptyCollectionException;
import exceptions.InvalidPositionException;
import exceptions.MyException;
import model.values.Value;

public interface OutInterface{
    void add(Value value);
    Value getFirst() throws EmptyCollectionException;
    void removeElementAt(int pos) throws InvalidPositionException;
    boolean isEmpty();
}

