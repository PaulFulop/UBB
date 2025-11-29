package items;

public class Apple extends Item {
    protected final String color;
    
    public Apple(int weight) {
        super(weight);
        this.color = "red";
    }

    public Apple(int weight, String color) {
        super(weight);
        this.color = color;
    }

    @Override
    public String toString() {
        return "Apple that weights "+ weight + " grams and has a " + color + " color";
    }
}
