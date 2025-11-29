package model.states;

import exceptions.EmptyCollectionException;
import exceptions.InvalidPositionException;
import exceptions.MyException;
import model.values.Value;

import java.util.LinkedList;
import java.util.List;

public class ArrayListOut implements OutInterface {
    private final List<Value> list;

    public ArrayListOut() {
        list = new LinkedList<Value>();
    }

    @Override
    public void add(Value value) {
        list.add(value);
    }

    @Override
    public Value getFirst() throws EmptyCollectionException {
        if (isEmpty()) throw new EmptyCollectionException();
        return list.getFirst();
    }

    @Override
    public void removeElementAt(int pos) throws InvalidPositionException {
        if (isEmpty() || pos < 0 || pos >= list.size()) throw new InvalidPositionException(pos);
        list.remove(pos);
    }

    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    public String toString() {
        String text = "";
        for (var val  : list) {
            text += val.toString() + '\n';
        }

        return text;
    }
}
