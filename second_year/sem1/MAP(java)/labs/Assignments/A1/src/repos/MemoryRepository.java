package repos;

import model.FoodInterface;
import model.Food;

import java.util.Arrays;

public class MemoryRepository implements RepositoryInterface {
    private static final int max_dim = RepositoryInterface.MAX_DIM;
    private Food[] data = new Food[max_dim];
    private int size;

    @Override
    public Food[] getAll() {
        return Arrays.copyOf(data, size);
    }

    @Override
    public Food getItem(int pos) {
        if (pos < 0 || pos > size) throw new IndexOutOfBoundsException("Out of bounds!\n");
        return data[pos];
    }

    @Override
    public int getSize() {
        return size;
    }

    @Override
    public void Add(Food food) {
        if(size >= max_dim) throw new IndexOutOfBoundsException("Out of bounds!\n");
        data[size++] = food;
    }

    @Override
    public void Remove(int pos) {
        if (pos < 0 || pos >= size) throw new IndexOutOfBoundsException("Out of bounds!\n");
        for(int i = pos; i < size; i++) {
            data[i] = data[i+1];
        }
        size--;
    }
}
