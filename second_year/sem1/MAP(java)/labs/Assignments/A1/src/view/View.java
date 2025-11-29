package view;

import controller.Controller;
import model.*;


// NOTE: for the commands I can/could make command classes for each specific command!

public class View {
    private final Controller controller;

    public View(){
        controller = new Controller();
    }

    public View(Controller controller){
        this.controller = controller;
    }

    public void printMenu(){
        IO.println("""
                \nASSIGNMENT 1
                
                Commands:
                1 -> display all expensive products
                2 -> add a new product
                3 -> remove a product
                4 -> see all products
                5 -> exit
                """);
    }

    public void StartMenu(){
        printMenu();
        while(true){
            try{
                String a = IO.readln("> ");
                int cmd = Integer.parseInt(a);

                switch(cmd){
                    case 1 -> {
                        var expensiveProducts = controller.getExpensiveProducts();
                        for (int i = 0; i < expensiveProducts.getSize(); i++) {
                            IO.println(expensiveProducts.getItem(i).toString());
                        }
                        IO.println();
                    }
                    case 2 -> {
                        String type = IO.readln("Insert the product type here (salt/sugar/flour): ");
                        type = type.toLowerCase();

                        if (type.equals("salt") || type.equals("sugar") || type.equals("flour")){
                            String priceTxt = IO.readln("Insert the price of the product here: ");
                            int price = Integer.parseInt(priceTxt);

                            String name = IO.readln("Insert the name of the product here: ");
                            Food newProduct;
                            if(type.equals("salt")){
                                newProduct = new Salt(price, name);
                            }
                            else if(type.equals("sugar")){
                                newProduct = new Sugar(price, name);
                            }
                            else{
                                newProduct = new Flour(price, name);
                            }

                            controller.AddProduct(newProduct);
                            IO.println("The new product has been added.\n");
                        }
                        else
                            IO.println("Invalid input!\n");
                    }
                    case 3 ->{
                        var repo = controller.getRepo();
                        for (int i = 0; i < repo.getSize(); i++) {
                            IO.println(i + " -> " + repo.getItem(i).toString());
                        }

                        String posTxt = IO.readln("\nSelect the position of the product you want to delete: ");
                        int pos = Integer.parseInt(posTxt);

                        controller.RemoveProduct(pos);
                        IO.println("The product has been deleted.\n");
                    }
                    case  4 -> {
                        if (controller.getRepo().getSize() == 0) IO.println("There are no products yet.\n");
                        else {
                            for (var item : controller.getRepo().getAll()) {
                                IO.println(item.toString());
                            }
                            IO.println();
                        }
                    }
                    case 5 -> {
                        IO.println("Goodbye!");
                        return;
                    }
                    default -> IO.println("Invalid input!\n");
                }
            }
            catch(Exception e){
                IO.println(e.getMessage());
            }
        }
    }
}
