import items.Apple;
import items.Book;
import items.Item;
import items.WeightedItem;

void main() throws Exception {
    var book1 = new Book(200, "Ana are mere");
    var apple1 = new Apple(300);
    var repo = new Repository();
    repo.addItem(book1);
    repo.addItem(apple1);
    for (var object : repo.getItems()) {
        try {
            IO.println(object.getWeight());
        }
        catch(NullPointerException e) {
            IO.println(e.getMessage());
            throw new Exception();
        }

        if (object instanceof Book book)
        {
            IO.println(book.getTitle());
        }
    }
    IO.println(Arrays.toString(repo.getItems().toArray()));
    Apple myApple = new Apple(300);
    Apple myNewApple = new Apple(300, "green");
    IO.println(myApple.toString());
    IO.println(myNewApple.toString());

    Book myBook = new Book(200);
    IO.println(myBook.getTitle());
}
