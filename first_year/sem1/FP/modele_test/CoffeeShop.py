
#function section

def add_coffee(coffee_list, coffee):
    """adds a coffee shop

    :param coffee_list: the list of coffees
    :type coffee_list: list
    :param coffee: the coffee shop to add
    :type coffee: list
    :raises ValueError: if the price is a negative number
    """
    if coffee[2] <= 0:
        raise ValueError("Invalid coffee price.")

    coffee_list.append(coffee)

def sort_coffees(coffee_list):
    """sorts the list of coffees alphabetically by country or ascending by price if countries are the same

    :param coffee_list: the list of coffees
    :type coffee_list: list
    :return: the sorted list of coffees
    :rtype: list
    """
    sorted_coffee_list = sorted(coffee_list[:], key=sort_by_country)

    # for i in range(len(sorted_coffee_list) - 1):
    #     if sorted_coffee_list[i][1] == sorted_coffee_list[i + 1][1]:
    #         if sorted_coffee_list[i][2] > sorted_coffee_list[i + 1][2]:
    #             sorted_coffee_list[i][2], sorted_coffee_list[i + 1][2] = sorted_coffee_list[i + 1][2], sorted_coffee_list[i][2]
    
    return sorted_coffee_list
    
def filter_coffee(coffee_list, country, price):
    """filters the coffees based on country name and prices smaller than the price parameter

    :param coffee_list: the list of coffees
    :type coffee_list: list
    :param country: the country of origin
    :type country: str
    :param price: the price of the coffee shop
    :type price: float
    :return: the filtered list
    :rtype: list
    """
    filtered = []
    for coffee in coffee_list:
        if coffee[1] == country and coffee[2] <= price:
            filtered.append(coffee)
    
    return filtered

def filter_coffee_country(coffee_list, country):
    """filters the coffees based on country name

    :param coffee_list: the list of coffees
    :type coffee_list: list
    :param country: the country of origin
    :type country: str
    :return: the filtered list
    :rtype: list
    """
    filtered = []
    for coffee in coffee_list:
        if coffee[1] == country:
            filtered.append(coffee)
    
    return filtered

def filter_coffee_price(coffee_list, price):
    """filters the coffees based on price

    :param coffee_list: the list of coffees
    :type coffee_list: list
    :param price: the price of the coffee shop
    :type price: float
    :return: the filtered list
    :rtype: list
    """
    filtered = []
    for coffee in coffee_list:
        if coffee[2] <= price:
            filtered.append(coffee)
    
    return filtered



def sort_by_country(coffee):
    """for sorting with multiple criteria

    :param coffee: the object in the list
    :type coffee: list
    :return: tuple with the values to compare between objects
    :rtype: tuple
    """
    return coffee[1].lower(), coffee[2]

#ui section

def start_app():
    coffee_list = [["meron", "Romania", 4.5], ["cfjapan", "Japan", 7.8], ["bonjour", "France", 5.2], ["coffee shop", "France", 12.3], ["ikebana", "Romania", 7.2]]
    print("List of commands:\n\n"
        "1 -> add coffee\n"
        "2 -> display coffees\n"
        "3 -> filter coffees\n"
        "4 -> exit app\n")
    
    while True:
        cmd = input("> ")
        
        match cmd:
            case "1":
                name = input("Insert the name here: ")
                country = input("Insert the country of origin here: ")

                try:
                    price = float(input("Insert price here: "))
                    coffee = [name, country, price]
                    add_coffee(coffee_list, coffee)
                    print("Added coffee.\n")
                except ValueError as e:
                    print(str(e) + "\n")
            case "2":
                display_coffees(coffee_list)
                print("\n")
            case "3":
                f_cmd = input("Insert the country and price to filter here (ex: france, 5.5): ").split()
                if len(f_cmd) == 1:
                    print("Filtered list of coffee shops:\n")
                    try:
                        price = float(f_cmd[0])
                        display_coffees(filter_coffee_price(coffee_list, price))
                        print("\n")
                    except ValueError:
                        display_coffees(filter_coffee_country(coffee_list, f_cmd[0]))
                        print("\n")
                elif len(f_cmd) == 2:
                    try:
                        country = f_cmd[0]
                        price = float(f_cmd[1])
                        display_coffees(filter_coffee(coffee_list, country, price))
                        print("\n")
                    except ValueError as e:
                        print(str(e) + "\n")
                else:
                    print("Only 2 properties for filtering.\n")
            case "4":
                return
            case _:
                print("Invalid option.\n")

def display_coffees(coffee_list):
    if len(coffee_list) == 0:
        print("No coffee shops in this list.")
        return
    
    sorted_coffee_list = sort_coffees(coffee_list)
    for coffee in sorted_coffee_list:
        print(f"Coffee name: {coffee[0]}, country: {coffee[1]}, price: {coffee[2]}")

start_app()