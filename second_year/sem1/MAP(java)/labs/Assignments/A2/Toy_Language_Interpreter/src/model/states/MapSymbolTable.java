package model.states;

import exceptions.DefinedIdException;
import exceptions.MyException;
import exceptions.UndefinedIdException;
import exceptions.ValueNotFoundException;
import model.statements.StatementInterface;
import model.values.Value;

import java.util.HashMap;
import java.util.Map;

public class MapSymbolTable implements SymbolTableInterface {
    private final Map<String, Value> map;

    public MapSymbolTable() {
        this.map = new HashMap<>();
    }
    public MapSymbolTable(Map<String, Value> map) {this.map = map;}

    @Override
    public Map<String, Value> getMap() {
        return map;
    }

    @Override
    public Value lookup(String key) throws UndefinedIdException, ValueNotFoundException {
        if (!isDefined(key)) throw new UndefinedIdException(key);

        var value = map.get(key);
        if (value == null) throw new ValueNotFoundException();
        return value;
    }

    @Override
    public boolean isDefined(String key) {
        return map.containsKey(key);
    }

    @Override
    public void add(String key, Value value) throws DefinedIdException {
        if (isDefined(key)) throw new DefinedIdException(key);
        map.put(key, value);
    }

    @Override
    public Value remove(String key) throws UndefinedIdException {
        if (!isDefined(key)) throw new UndefinedIdException(key);
        return map.remove(key);
    }
    
    @Override
    public void update(String key, Value val) throws UndefinedIdException {
        if (!isDefined(key)) throw new UndefinedIdException(key);
        map.put(key, val);
    }

    @Override
    public String toString() {
        String text = "";
        for (var key  : map.keySet()) {
            text += key + " --> " + map.get(key) + '\n';
        }

        return text;
    }
}
