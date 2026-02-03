package controller;

import model.states.map.tables.HeapTable;
import model.states.map.tables.SymbolTable;
import model.values.RefValue;

import java.util.*;
import java.util.stream.Collectors;

// THE REFERENCE VALUE REFERS TO NULL WHEN ITS ADDRESS IS 0

public class GarbageCollector {
    // for every Reference value R in symbol table values:
    // addressesToKeep.add(R.address)
    // If the referred value is also a reference,
    // Then follow the reference chain and add all relevant addresses.
    //
    // var addressesToClean = heap.allAddressed() \ addressesToKeep

    // A5:
    // Same as above, but compute a UNION of the values for all
    // symbol values

    public void run(List<SymbolTable>allSymbolTables, HeapTable heapTable) {
        Set<Integer> addressesToKeep = new HashSet<>();

        for(var symbolTable : allSymbolTables){
            var symTableAddresses = getAddressesFromSymbolTable(symbolTable);

            // add all the addresses from symbol table here + all the reachable ones from each address
            for(var address : symTableAddresses) {
                addressesToKeep.addAll(getReachableAddressChain(symbolTable, heapTable, address));
            }
        }

        // look which addresses are on the heap but don't appear in addressesToKeep
        var heapAddresses = new HashSet<>(heapTable.getMap().keySet());
        for(var address : heapAddresses){
            if (!addressesToKeep.contains(address)) {
                heapTable.remove(address);
            }
        }
    }

    private List<Integer> getAddressesFromSymbolTable(SymbolTable symTable) {
        return symTable.getMap().values().stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> {RefValue v1 = (RefValue) v; return v1.getAddress();})
                .collect(Collectors.toList());
    }

    private Set<Integer> getReachableAddressChain(SymbolTable symTable, HeapTable heapTable, int address) {
        if (address == 0) return new HashSet<>(); // null address (maybe throw exception here)

        Set<Integer> visited = new HashSet<>();

        // RISK IF THERE'S A LOOP IN THIS REFERENCE CHAIN => INFINITE LOOP! (if I don't check visited)
        visited.add(address);
        while(isAddressToRef(heapTable, address)) {
            address = ((RefValue) heapTable.getMap().get(address)).getAddress();
            if (visited.contains(address)) break; // detect cycles
            visited.add(address);
        }
        return visited;
    }

    //check whether the address points to another reference value or not
    private Boolean isAddressToRef(HeapTable heapTable, int address) {
        var value = heapTable.getMap().get(address);
        return value instanceof RefValue;
    }
}