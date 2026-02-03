package model.states.map.tables;

import exceptions.UndefinedIdException;
import exceptions.ValueNotFoundException;
import model.states.map.MyHeap;

public class LockTable extends MyHeap<Integer> {
    public synchronized Integer lookup(Integer key) throws UndefinedIdException, ValueNotFoundException {
        return super.lookup(key);
    }

    public synchronized void update(Integer key, Integer value) throws UndefinedIdException {
        super.update(key, value);
    }

    public synchronized int add(Integer value) {
        return super.add(value);
    }

    protected synchronized void updateFreeLocation() {
        super.updateFreeLocation();
    }
}
