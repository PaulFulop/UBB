from functions import create_animal, to_str_animal, add_animal, modify_type, change_types, sort_animals_ascending_by_name, filter_animals_by_type

#animal: code(str), name(str), type(str), species(str)

def menu(animals:list) -> None:
    print("List of commands:\n"
          "1 -> add an animal\n"
          "2 -> modify the type of an animal\n"
          "3 -> change types of all animals with given species\n"
          "4 -> show all animals\n"
          "5 -> exit the app\n")
    
    while True:
        cmd = input("> ")

        match cmd:
            case "1":
                try:
                    code = input("Insert the code here: ")
                    name = input("Insert the name here: ")
                    type = input("Insert the type here: ")
                    species = input("Insert the species here: ")
                    new_animal = create_animal(code, name, type, species)
                    add_animal(animals, new_animal)
                    print("New animal was added.\n")
                except ValueError as e:
                    print(str(e) + "\n")
            case "2":
                code = input("Insert the code to look for the animal here: ")
                new_type = input("Insert the new type here: ")
                modify_type(animals, code, new_type)
                print("Type of the animal was modified.\n")
            case "3":
                try:
                    species = input("Insert the species you want to change the type for here: ")
                    new_type = input("Insert the new type here: ")
                    change_types(animals, species, new_type)
                    print("Type of all animals with the given species were modified.\n")
                except ValueError as e:
                    print(str(e) + "\n")
            case "4":
                type = input("Insert the type of the animals you want to see here: ")
                show_animals(animals, type)
            case "5":
                print("Exiting...")
                return
            case _:
                print("Invalid command.\n")

def show_animals(animals:list, type:str) -> None:
    animals_filtered_by_type = filter_animals_by_type(animals, type)
    animals_sorted_by_name = sort_animals_ascending_by_name(animals_filtered_by_type)

    for animal in animals_sorted_by_name:
        print(to_str_animal(animal))