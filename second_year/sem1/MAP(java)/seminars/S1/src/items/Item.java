package items;

public abstract class Item implements WeightedItem {

    protected final int weight;

    protected Item(int weight) {
        this.weight = weight;
    }

    public int getWeight() {
        return weight;
    }
}
