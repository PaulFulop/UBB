#coffee : name(str), country(str), price(float)

def create_coffee(name:str, country:str, price:float) -> list:
    return [name, country, price]

def get_name(coffee:list) -> str:
    return coffee[0]

def get_country(coffee:list) -> str:
    return coffee[1]

def get_price(coffee:list) -> float:
    return coffee[2]

def set_name(coffee:list, new_name:str) -> None:
    coffee[0] = new_name

def set_country(coffee:list, new_country:str) -> None:
    coffee[1] = new_country

def set_name(coffee:list, new_price:float) -> None:
    coffee[2] = new_price

def to_str_coffee(coffee:list) -> str:
    return f"Coffee {get_name(coffee)}, originally from {get_country(coffee)} and with the price of {get_price(coffee)} RON."

def add_coffee(coffees:list, coffee:list) -> None:
    """adds a coffee to the list of coffees

    :param coffees: the list of coffees
    :type coffees: list
    :param coffee: the coffee to add
    :type coffee: list
    :raises ValueError: if the price of the new coffee is negative
    """
    if get_price(coffee) <= 0:
        raise ValueError("Invalid price.")

    coffees.append(coffee)

def test_add_coffee():
    coffees = []
    add_coffee(coffees, ["Caffe miel", "France", 4.5])
    assert len(coffees) == 1, "Error.Adding doesn't work."

    try:
        add_coffee(coffees, ["Meron", "Romania", -1])
        print("Error.Ths should not be added.")
    except ValueError as e:
        assert str(e) == "Invalid price.", "Error."

#test_add_coffee()

def sort_coffees(coffees:list) -> list:
    sorted_coffees = coffees[:]

    for i in range(len(coffees) - 1):
        for j in range(i + 1, len(coffees)):
            if get_country(sorted_coffees[i]).lower() > get_country(sorted_coffees[j]).lower() or get_country(sorted_coffees[i]).lower() == get_country(sorted_coffees[j]).lower() and get_price(sorted_coffees[i]) > get_price(sorted_coffees[j]):
                sorted_coffees[i], sorted_coffees[j] = sorted_coffees[j], sorted_coffees[i]
    
    return sorted_coffees

def filter_coffees(coffees:list, country:str, price:float) -> list:
    filtered_by_country, filtered_by_price, filtered = [], [], []
    for coffee in coffees:
        if get_country(coffee).lower() == country.lower():
            filtered_by_country.append(coffee)

    for coffee in coffees:
        if get_price(coffee) <= price:
            filtered_by_price.append(coffee)

    if country == "":
        return filtered_by_price
    
    if price == -1:
        return filtered_by_country
    
    for coffee in filtered_by_country:
        if get_price(coffee) <= price:
            filtered.append(coffee)
    
    return filtered

def delete_coffees(coffees:list, country:str):
    coffees_copy = coffees[:]

    for coffee in coffees_copy:
        if get_country(coffee) == country:
            coffees.remove(coffee)