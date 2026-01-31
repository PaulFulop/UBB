package model.states;
import model.values.IntValue;
import model.values.Value;

// TODO see if this works right

public class MyHeap extends MyMap<IntValue, Value> {
    private int freeLocation;

    public MyHeap() {
        super();
        this.freeLocation = 1;
    }

    public int add(Value value) { // returns the address in which the value was added
        super.add(new IntValue(freeLocation), value);
        int oldFreeLocation = freeLocation;
        updateFreeLocation();
        return oldFreeLocation;
    }

    private void updateFreeLocation() {
        int i;
        for (i = 1; i <= map.size(); i++) {
            if (!isDefined(new IntValue(i))) {
                freeLocation = i;
                return;
            }
        }
        freeLocation = i;
    }
}
