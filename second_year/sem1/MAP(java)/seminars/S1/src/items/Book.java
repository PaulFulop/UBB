package items;

public class Book extends Item {

    private final String title;

    public Book(int weight) {
        super(weight);
        this.title = "No title";
    }

    public Book(int weight, String title) {
        super(weight);
        this.title = title;
    }

    public String getTitle() {
        return title;
    }

    @Override
    public String toString() {
        return "items.Book{" +
                "weight=" + getWeight() +
                '}';
    }
}
