package model;

public class Sugar extends Food {
    public Sugar(int price, String productName) {
        super(price, productName);
    }

    @Override
    public String toString() {
        return "sugar: " + productName + ' ' + price + " ron/kg.";
    }
}
