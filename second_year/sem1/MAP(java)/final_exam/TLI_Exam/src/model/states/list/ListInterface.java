package model.states.list;

import exceptions.EmptyCollectionException;
import exceptions.InvalidPositionException;

import java.util.List;

public interface ListInterface<T> {
    void add(T value);
    T getFirst() throws EmptyCollectionException;
    void removeElementAt(int pos) throws InvalidPositionException;
    boolean isEmpty();
    List<T> getElements();
}

