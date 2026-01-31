package model.states;

import exceptions.EmptyCollectionException;
import exceptions.InvalidPositionException;
import model.values.Value;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

public class MyList<T> implements ListInterface<T> {
    private final List<T> list;

    public MyList() {
        this.list = new CopyOnWriteArrayList<>();
    }

    @Override
    public void add(T value) {
        list.add(value);
    }

    @Override
    public T getFirst() throws EmptyCollectionException {
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

    @Override
    public List<T> getElements() {
        return list;
    }

    public String toString() {
        String text = "";
        for (var val  : list) {
            text += val.toString() + '\n';
        }

        return text;
    }
}
