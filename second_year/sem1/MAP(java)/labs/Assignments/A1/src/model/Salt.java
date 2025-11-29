package model;

public class Salt extends Food {
    public Salt(int price, String productName) {
        super(price, productName);
    }

    @Override
    public String toString() {
        return "salt: " + productName + ' ' + price + " ron/kg.";
    }
}
