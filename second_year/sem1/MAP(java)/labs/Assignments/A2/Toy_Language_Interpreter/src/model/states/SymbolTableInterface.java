package model.states;

import exceptions.DefinedIdException;
import exceptions.MyException;
import exceptions.UndefinedIdException;
import exceptions.ValueNotFoundException;
import model.values.Value;

import java.util.Map;

public interface SymbolTableInterface{
    Value lookup(String key) throws UndefinedIdException, ValueNotFoundException;
    boolean isDefined(String key);
    void add(String key, Value value) throws DefinedIdException;
    Value remove(String key) throws UndefinedIdException;
    void update(String name, Value val) throws UndefinedIdException;
    Map<String, Value> getMap();
}