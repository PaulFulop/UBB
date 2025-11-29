package repos;

import model.Food;

public interface RepositoryInterface {
    int MAX_DIM = 10;
    Food[] getAll();
    Food getItem(int pos);
    int getSize();
    void Add(Food food);
    void Remove(int pos);
}
