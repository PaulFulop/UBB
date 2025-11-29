package model.types;

import model.values.BoolValue;
import model.values.Value;

public class BoolType implements Type {

    public static final BoolType INSTANCE = new BoolType();
    private BoolType() {}

    @Override
    public boolean equals(Object another){
        return another instanceof BoolType;
    }

    @Override
    public String toString() { return "bool";}

    @Override
    public Value getDefaultValue() {
        return new BoolValue(false);
    }
}

