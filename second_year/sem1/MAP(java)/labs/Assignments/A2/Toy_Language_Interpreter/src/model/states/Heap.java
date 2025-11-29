package model.states;


import exceptions.UndefinedIdException;
import exceptions.ValueNotFoundException;
import model.values.IntValue;
import model.values.Value;

import java.util.HashMap;
import java.util.Map;

public class Heap implements HeapInterface {
    private final Map<IntValue, Value> map;
    private int freeLocation;

    public Heap() {
        this.map = new HashMap<>();
        this.freeLocation = 1;
    }

    @Override
    public Map<IntValue, Value> getMap() {
        return map;
    }

    @Override
    public void setMap(Map<IntValue, Value> map) {
        this.map.clear();
        this.map.putAll(map);
    }

    @Override
    public Value lookup(int key) throws UndefinedIdException, ValueNotFoundException {
        if (!isDefined(key)) throw new UndefinedIdException(String.valueOf(key));
        var value = map.get(new IntValue(key));

        if (value == null) throw new ValueNotFoundException();
        return value;
    }

    @Override
    public boolean isDefined(int key) {
        return map.containsKey(new IntValue(key));
    }

    @Override
    public int add(Value value) { // returns the address in which the value was added
        map.put(new IntValue(freeLocation), value);
        int oldFreeLocation = freeLocation;
        updateFreeLocation();
        return oldFreeLocation;
    }

    @Override
    public Value remove(int key) throws UndefinedIdException {
        if (!isDefined(key)) throw new UndefinedIdException(String.valueOf(key));
        return map.remove(new IntValue(key));
    }

    @Override
    public void update(int key, Value value) throws UndefinedIdException {
        if (!isDefined(key)) throw new UndefinedIdException(String.valueOf(key));
        map.put(new IntValue(key), value);
    }

    private void updateFreeLocation() {
        int i;
        for (i = 1; i <= map.size(); i++) {
            if (!isDefined(i)) {
                freeLocation = i;
                return;
            }
        }
        freeLocation = i;
    }

    @Override
    public String toString(){
        String text = "";
        for (var key  : map.keySet()) {
            text += key.val() + " --> " + map.get(key).toString() + '\n';
        }

        return text;
    }
}
