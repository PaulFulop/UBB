package model.states.map.tables;

import exceptions.UndefinedIdException;
import exceptions.ValueNotFoundException;
import javafx.util.Pair;
import model.states.map.MyHeap;

import java.util.List;

public class BarrierTable extends MyHeap<Pair<Integer, List<Integer>>> {

    public synchronized Pair<Integer, List<Integer>> lookup(Integer key) throws UndefinedIdException, ValueNotFoundException {
        return super.lookup(key);
    }

    public synchronized void update(Integer key, Pair<Integer, List<Integer>> value) throws UndefinedIdException {
        super.update(key, value);
    }

    public synchronized int add(Pair<Integer, List<Integer>> value) {
        return super.add(value);
    }

    protected synchronized void updateFreeLocation() {
        super.updateFreeLocation();
    }
}
