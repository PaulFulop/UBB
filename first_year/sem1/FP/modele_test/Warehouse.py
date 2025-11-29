

#warehouse content: name(str), quantity(int), price(int)

#functions 
def add_content(contents:list, content:list) -> None:
    if content[1] <= 0 or content[2] <= 0:
        raise ValueError("Invalid price or quantity.")

    contents.append(content)

def remove_content(contents:list, prod_name:str) -> None:
    """removes the product/content with the given name

    :param contents: the list of contents
    :type contents: list
    :param prod_name: the name of the product/content we want to remove
    :type prod_name: str
    :raises ValueError: if the produt/content with this name does not exist
    """
    found = False
    for content in contents:
        if content[0] == prod_name:
            found = True
            contents.remove(content)
            break
    
    if not found:
        raise ValueError("Item does not exist.") 

def calculate_total_value(contents:list) -> int:
    total_value = 0
    for content in contents:
        total_value += content[1] * content[2]
    
    return total_value

def sort_contents(contents:list) -> list:
    sorted_contents = contents[:]
    for i in range(len(contents) - 1):
        for j in range(i + 1, len(contents)):
            if sorted_contents[i][0] < sorted_contents[j][0]:
                sorted_contents[i], sorted_contents[j] = sorted_contents[j], sorted_contents[i]
    
    return sorted_contents

#ui
def start_app():
    contents = [["prod1", 10, 10], ["prod2", 10, 1], ["prod3", 10, 2], ["prod4", 10, 3]]
    print("List of commands you can use:\n"
          "add <product_name> <quantity> <item_price>\n"
          "remove <product_name>\n"
          "list all\n"
          "list total\n"
          "exit\n")
    while True:
        cmd = input("> ").split()
        for cd in cmd:
            cd = cd.strip()
        
        match cmd[0].lower():
            case "add":
                if len(cmd) != 4:
                    print("Invalid command.\n")
                else:
                    try:
                        prod_name = cmd[1]
                        quantity = int(cmd[2])
                        price = int(cmd[3])
                        add_content(contents, [prod_name, quantity, price])
                        print("Added product/content.\n")
                    except ValueError as e:
                        print(str(e) + "\n")
            case "remove":
                if len(cmd) != 2:
                    print("Invalid command.\n")
                else:
                    try:
                        prod_name = cmd[1]
                        remove_content(contents, prod_name)
                        print("Removed product/content.\n")
                    except ValueError as e:
                        print(str(e) + "\n")

            case "list":
                if cmd[1].lower() == "all":
                    list_contents(contents)
                elif cmd[1].lower() == "total":
                    list_total_value(contents)
                else:
                    print("Invalid command.\n")
            case "exit":
                if len(cmd) == 1:
                    print("Exiting...")
                    return
                else:
                    print("Invalid command.\n")
            case _:
                print("Invalid command.\n")


def list_contents(contents:list) -> None:
    if len(contents) == 0:
        print("We don't have contents/products yet.\n")
        return
    
    sorted_contents = sort_contents(contents)
    for content in sorted_contents:
        print(f"Content/product with name: {content[0]}, quantity: {content[1]}, price: {content[2]}.")
    print("\n")

def list_total_value(contents:list) -> None:
    if len(contents) == 0:
        print("We don't have contents/products yet.\n")
        return
    
    total_value = calculate_total_value(contents)
    print(f"The total value of all the products/contents is {total_value}.\n")

start_app()