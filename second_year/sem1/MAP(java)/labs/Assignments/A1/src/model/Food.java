package model;

public class Food implements FoodInterface {
    protected String productName;
    protected int price;

    public Food(int price, String productName) {
        if (price <= 0) throw new IllegalArgumentException("Price cannot be negative or zero!\n");
        this.price = price;
        this.productName = productName;
    }

    @Override
    public boolean isExpensive() {
        return price > 20;
    }
}
