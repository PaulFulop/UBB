package model.states.map;

public class MyHeap<V> extends MyMap<Integer, V> {
    protected int freeLocation;

    public MyHeap() {
        super();
        this.freeLocation = 1;
    }

    public int add(V value) { // returns the address in which the value was added
        super.add(freeLocation, value);
        int oldFreeLocation = freeLocation;
        updateFreeLocation();
        return oldFreeLocation;
    }

    protected void updateFreeLocation() {
        int i;
        for (i = 1; i <= map.size(); i++) {
            if (!isDefined(i)) {
                freeLocation = i;
                return;
            }
        }
        freeLocation = i;
    }
}
