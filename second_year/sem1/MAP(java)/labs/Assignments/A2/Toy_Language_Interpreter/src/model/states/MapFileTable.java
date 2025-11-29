package model.states;

import exceptions.DefinedIdException;
import exceptions.UndefinedIdException;
import exceptions.ValueNotFoundException;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.util.HashMap;
import java.util.Map;


public class MapFileTable implements FileTableInterface {
    private final Map<StringValue, BufferedReader> map;

    public MapFileTable() {
        this.map = new HashMap<>();
    }

    @Override
    public BufferedReader lookup(StringValue key) throws UndefinedIdException, ValueNotFoundException {
        if (!isDefined(key)) throw new UndefinedIdException(key.val());

        var value = map.get(key);
        if (value == null) throw new ValueNotFoundException();
        return value;
    }

    @Override
    public boolean isDefined(StringValue key) {
        return map.containsKey(key);
    }

    @Override
    public void add(StringValue key, BufferedReader value) throws DefinedIdException {
        if (isDefined(key)) throw new DefinedIdException(key.val());
        map.put(key, value);
    }

    @Override
    public BufferedReader remove(StringValue key) throws UndefinedIdException {
        if (!isDefined(key)) throw new UndefinedIdException(key.val());
        return map.remove(key);
    }

    @Override
    public void update(StringValue key, BufferedReader value) throws UndefinedIdException {
        if (!isDefined(key)) throw new UndefinedIdException(key.val());
        map.put(key, value);
    }

    @Override
    public Map<StringValue, BufferedReader> getMap() {
        return map;
    }

    @Override
    public String toString() {
        String text = "";
        for (var key  : map.keySet()) {
            text += key.val() + " --> " + map.get(key).toString() + '\n';
        }

        return text;
    }
}
