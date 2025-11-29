#animal: code(str), name(str), type(str), species(str)

def create_animal(code:str, name:str, type:str, species:str) -> list:
    return [code, name, type, species]

def get_code(animal:list) -> str:
    return animal[0]

def get_name(animal:list) -> str:
    return animal[1]

def get_type(animal:list) -> str:
    return animal[2]

def get_species(animal:list) -> str:
    return animal[3]

def set_code(animal:list, code:str) -> None:
    animal[0] = code

def set_name(animal:list, name:str) -> None:
    animal[1] = name

def set_type(animal:list, type:str) -> None:
    animal[2] = type

def set_species(animal:list, species:str) -> None:
    animal[3] = species

def to_str_animal(animal:list) -> str:
    return f"{animal[3]} with code {animal[0]}, having the name {animal[1]}. ({animal[2]})"

def add_animal(animals:list, new_animal:list) -> None:
    """adds an animal in the zoo

    :param animals: the list of animals
    :type animals: list
    :param new_animal: the animal to add in the zoo
    :type new_animal: list
    :raises ValueError: if one of the "properties" of the new animal to add in the zoo is missing
    :raises ValueError: if the code of the new animal is already used
    """
    if get_code(new_animal) == '' or get_name(new_animal) == '' or get_type(new_animal) == '' or get_species(new_animal) == '':
        raise ValueError("One of the fields is void.")
    
    for animal in animals:
        if get_code(animal) == get_code(new_animal):
            raise ValueError("The animal with this code is already in the zoo.")
    
    animals.append(new_animal)

def test_add_animal() -> None:
    list = []
    add_animal(list, ["1234", "rex", "carnivore", "lion"])
    assert len(list) == 1, "Error."

    try:
        add_animal(list, ["1234", "rex", "carnivore", "lion"])
    except ValueError as e:
        assert str(e) == "The animal with this code is already in the zoo."
    
    try:
        add_animal(list, ["1321", "", "carnivore", "lion"])
    except ValueError as e:
        assert str(e) == "One of the fields is void."

#test_add_animal()

def modify_type(animals:list, code:str, new_type:str) -> None:    
    for i in range(len(animals)):
        if get_code(animals[i]) == code:
            set_type(animals[i], new_type)
            return

def change_types(animals:list, species:str, new_type:str) -> None:
    if new_type == "":
        raise ValueError("Invalid type.")
    
    for i in range(len(animals)):
        if get_species(animals[i]) == species:
            set_type(animals[i], new_type)

def sort_animals_ascending_by_name(animals:list) -> list:
    sorted_animals = animals[:]

    for i in range(len(animals) - 1):
        for j in range(i + 1, len(animals)):
            if get_name(sorted_animals[i]) > get_name(sorted_animals[j]):
                sorted_animals[i], sorted_animals[j] = sorted_animals[j], sorted_animals[i]
    return sorted_animals

def filter_animals_by_type(animals:list, type:str) -> list:
    filtered = []
    for animal in animals:
        if get_type(animal) == type:
            filtered.append(animal)
    return filtered