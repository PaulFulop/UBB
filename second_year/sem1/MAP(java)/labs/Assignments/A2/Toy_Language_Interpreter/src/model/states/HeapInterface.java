package model.states;

import exceptions.UndefinedIdException;
import exceptions.ValueNotFoundException;
import model.values.IntValue;
import model.values.Value;
import java.util.Map;

public interface HeapInterface {
    Value lookup(int key) throws UndefinedIdException, ValueNotFoundException;
    boolean isDefined(int key);
    int add(Value value);
    Value remove(int key) throws UndefinedIdException;
    void update(int key, Value value) throws UndefinedIdException;
    Map<IntValue, Value> getMap();
    void setMap(Map<IntValue, Value> map);
}
