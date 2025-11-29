package controller;

import repos.MemoryRepository;
import repos.RepositoryInterface;
import model.Food;

public class Controller {
    private final RepositoryInterface repo;

    public Controller() {
        this.repo = new MemoryRepository();
    }

    public Controller(RepositoryInterface repo) {
        this.repo = repo;
    }

    public void AddProduct(Food food) {
        this.repo.Add(food);
    }

    public void RemoveProduct(int pos) {
        this.repo.Remove(pos);
    }

    public RepositoryInterface getRepo() {
        return repo;
    }

    public RepositoryInterface getExpensiveProducts() {
        RepositoryInterface expensiveProducts = new MemoryRepository();

        for(int i = 0; i < this.repo.getSize(); ++i){
            var currentItem = repo.getItem(i);
            if(currentItem != null && currentItem.isExpensive()){
                expensiveProducts.Add(currentItem);
            }
        }

        if (expensiveProducts.getSize() == 0)
            throw new RuntimeException("Expensive products not found.\n");

        return expensiveProducts;
    }
}
