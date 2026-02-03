package model.states.map.tables;

import model.states.map.MyMap;
import model.values.Value;

public class SymbolTable extends MyMap<String, Value> {
    public SymbolTable deepcopy() {
        SymbolTable symbolTableCopy = new SymbolTable();
        for(var entry : map.entrySet()){
            symbolTableCopy.add(entry.getKey(), entry.getValue().copy());
        }

        return symbolTableCopy;
    }
}
