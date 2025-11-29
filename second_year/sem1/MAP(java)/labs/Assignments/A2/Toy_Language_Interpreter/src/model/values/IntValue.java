package model.values;

import model.types.IntType;
import model.types.StringType;
import model.types.Type;

public record IntValue(int val) implements Value {

    @Override
    public String toString() {
        return Integer.toString(val);
    }

    public Type getType() {
        return IntType.INSTANCE;
    }

    @Override
    public boolean equals(Object another){
        return another instanceof IntValue;
    }
}

