import items.WeightedItem;

import java.util.ArrayList;
import java.util.List;

public class Repository {
    private final List<WeightedItem> items = new ArrayList<>();

    public List<WeightedItem> getItems() {
        return items;
    }

    public void addItem(WeightedItem item) {
        items.add(item);
    }

}
