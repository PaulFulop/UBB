package model.states;

import exceptions.DefinedIdException;
import exceptions.UndefinedIdException;
import exceptions.ValueNotFoundException;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class MyMap<K, V> implements MapInterface<K, V> {
    protected final Map<K, V> map;

    public MyMap() {this.map = new ConcurrentHashMap<K, V>();}

    public MyMap(Map<K, V> map) {
        this.map = map;
    }

    @Override
    public V lookup(K key) throws UndefinedIdException, ValueNotFoundException {
        if (!isDefined(key)) throw new UndefinedIdException(String.valueOf(key));
        var value = map.get(key);

        if (value == null) throw new ValueNotFoundException();
        return value;
    }

    @Override
    public boolean isDefined(K key) {
        return map.containsKey(key);
    }

    @Override
    public void add(K key, V value) throws DefinedIdException {
        if (isDefined(key)) throw new DefinedIdException(key.toString());
        map.put(key, value);
    }

    @Override
    public V remove(K key) throws UndefinedIdException {
        if (!isDefined(key)) throw new UndefinedIdException(key.toString());
        return map.remove(key);
    }

    @Override
    public void update(K key, V value) throws UndefinedIdException {
        if (!isDefined(key)) throw new UndefinedIdException(key.toString());
        map.put(key, value);
    }

    @Override
    public Map<K, V> getMap() {
        return map;
    }

    @Override
    public void setMap(Map<K, V> map) {
        this.map.clear();
        this.map.putAll(map);
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
