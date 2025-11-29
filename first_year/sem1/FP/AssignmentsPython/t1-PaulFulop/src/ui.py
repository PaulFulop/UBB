from functions import create_coffee, to_str_coffee, add_coffee, sort_coffees, filter_coffees, delete_coffees

#coffee : name(str), country(str), price(float)

def menu(coffees:list) -> None:
    print("List of all commands:\n\n"
          "1 -> add a coffee\n"
          "2 -> display all coffees sorted by country\n"
          "3 -> filter coffees with given country and price\n"
          "4 -> delete all coffees with given country\n\n")
    
    while True:
        cmd = input("> ")

        match cmd:
            case "1":
                try:
                    name = input("Insert the name of the coffee here: ")
                    country = input("Insert the country of origin here: ")
                    price = float(input("Insert the price of the coffee here: "))
                    new_coffee = create_coffee(name, country, price)
                    add_coffee(coffees, new_coffee)
                    print("New coffee added.\n")
                except ValueError as e:
                    print(str(e) + "\n")
            case "2":
                display_sorted_coffees(coffees)
                print("\n")
            case "3":
                country = input("Insert the country of origin here: ")
                price = input("Insert the price of the coffee here: ")

                if price == "":
                    price = -1
                    display_filtered_coffees(coffees, country, price)
                    print("\n")
                else:
                    try:
                        price = float(price)
                        display_filtered_coffees(coffees, country, price)
                        print("\n")
                    except ValueError as e:
                        print(str(e) + "\n")
            case "4":
                country = input("Insert the country of origin here: ")
                delete_coffees(coffees, country)
                print("Deleted coffees with given country of origin.\n")
            case _:
                print("Invalid command.\n")

def display_sorted_coffees(coffees:list) -> None:
    sorted_coffees = sort_coffees(coffees)
    for coffee in sorted_coffees:
        print(to_str_coffee(coffee))

def display_filtered_coffees(coffees:list, country:str, price:float) -> None:
    filtered_coffees = filter_coffees(coffees, country, price)
    if len(filtered_coffees) == 0:
        print("No such coffees")
        return

    for coffee in filtered_coffees:
        print(to_str_coffee(coffee))