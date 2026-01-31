package model.values;

import model.types.BoolType;
import model.types.StringType;
import model.types.Type;

public record BoolValue(boolean val) implements Value {

    @Override
    public String toString() {
        return val ? "true" : "false";
    }

    @Override
    public Type getType() {
        return BoolType.INSTANCE;
    }

    @Override
    public Value copy() {
        return new BoolValue(val);
    }

    @Override
    public boolean equals(Object another){
        return another instanceof BoolValue;
    }
}
