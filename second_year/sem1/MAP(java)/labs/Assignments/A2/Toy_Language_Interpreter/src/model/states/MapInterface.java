package model.states;

import exceptions.DefinedIdException;
import exceptions.UndefinedIdException;
import exceptions.ValueNotFoundException;
import model.values.IntValue;
import model.values.Value;

import java.util.Map;

public interface MapInterface<K, V> {
    V lookup(K key) throws UndefinedIdException, ValueNotFoundException;
    boolean isDefined(K key);
    void add(K key, V value) throws DefinedIdException;
    V remove(K key) throws UndefinedIdException;
    void update(K key, V value) throws UndefinedIdException;
    Map<K, V> getMap();
    void setMap(Map<K, V> map);
}
