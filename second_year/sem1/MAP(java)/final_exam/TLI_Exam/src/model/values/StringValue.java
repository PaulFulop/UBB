package model.values;

import model.types.StringType;
import model.types.Type;

public record StringValue(String val) implements Value {
    @Override
    public String toString() {
        return val;
    }

    @Override
    public Type getType() {
        return StringType.INSTANCE;
    }

    @Override
    public Value copy() {
        return new  StringValue(val);
    }

    @Override
    public boolean equals(Object another){
        return another instanceof StringValue;
    }
}
