package model.types;

import model.values.StringValue;
import model.values.Value;

public class StringType implements Type {

    public static final StringType INSTANCE = new StringType();
    private StringType() {}

    @Override
    public boolean equals(Object another){
        return another instanceof StringType;
    }

    @Override
    public String toString() { return "string";}

    @Override
    public Value getDefaultValue() {
        return new StringValue("nil");
    }

    @Override
    public Type copy() {
        return StringType.INSTANCE;
    }
}
