package model.states;

import exceptions.DefinedIdException;
import exceptions.UndefinedIdException;
import exceptions.ValueNotFoundException;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.util.Map;


public interface FileTableInterface {
    BufferedReader lookup(StringValue key) throws UndefinedIdException, ValueNotFoundException;
    boolean isDefined(StringValue key);
    void add(StringValue key, BufferedReader value) throws DefinedIdException;
    BufferedReader remove(StringValue key) throws UndefinedIdException;
    void update(StringValue key, BufferedReader value) throws UndefinedIdException;
    Map<StringValue, BufferedReader> getMap();
}
