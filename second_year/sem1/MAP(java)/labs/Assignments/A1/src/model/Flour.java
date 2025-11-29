package model;

public class Flour extends Food {
    public Flour(int price, String productName) {
        super(price, productName);
    }

    @Override
    public String toString() {
        return "flour: " + productName + ' ' + price + " ron/kg.";
    }
}
