package model.types;
import model.values.Value;
import model.values.RefValue;


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

    @Override
    public Type copy() {
        return new RefType(inner.copy());
    }

}
