package model.values;

import model.types.RefType;
import model.types.Type;

public record RefValue(int address, Type valueType) implements Value {
    @Override
    public Type getType() {
        return new RefType(valueType);
    }

    @Override
    public Value copy() {
        return new RefValue(address, valueType);
    }

    public int getAddress() {
        return address;
    }

    @Override
    public String toString() {
        return "RefValue(" + address + ", " + valueType + ')';
    }
}
