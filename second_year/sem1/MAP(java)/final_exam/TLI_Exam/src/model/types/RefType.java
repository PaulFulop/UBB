package model.types;
import com.sun.jdi.BooleanType;
import model.values.Value;
import model.values.RefValue;

import java.util.Objects;

public record RefType(Type inner) implements Type {
    public boolean equals(Object another) {
        return another instanceof RefType;
    }

    public Type getInnerType() {
        return inner;
    }

    @Override
    public String toString() {
        return "RefType(" + inner.toString() + ")";
    }

    @Override
    public Value getDefaultValue() {
        return new RefValue(0, inner);
    }

}
