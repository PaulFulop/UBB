
#flight: code(str), duration (int), dep_city(str), dest_city(str)

#functions
def add_flight(flights:list, flight:list) -> None:
    if len(flight[0]) < 3 or len(flight[2]) < 3 or len(flight[3]) < 3 or flight[1] < 20:
        raise ValueError("Invalid data.")

    flights.append(flight)

def delete_flight(flights:list, code:str) -> None:
    """deletes a flight with the given code

    :param flights: the list of flights
    :type flights: list
    :param code: the code of the flight to delete
    :type code: str
    :raises ValueError: if there is no flight with this code
    """
    initial_len = len(flights)
    for flight in flights:
        if flight[0] == code:
            flights.remove(flight)
            break
    
    if initial_len == len(flights):
        raise ValueError("No flight with such code")
    
def sort_flights(flights:list) -> list:
    sorted_flights = flights[:]
    for i in range(len(flights) - 1):
        for j in range(i + 1, len(flights)):
            if sorted_flights[i][3] > sorted_flights[j][3]:
                sorted_flights[i], sorted_flights[j] = sorted_flights[j], sorted_flights[i]
    return sorted_flights

def change_duration(flights:list, departure_city:str, new_duration:int) -> None:
    if new_duration < 10 or new_duration > 60:
        raise ValueError("Invalid duration.")
    
    changed = False
    for flight in flights:
        if flight[2] == departure_city:
            changed = True
            flight[1] = new_duration
    
    if changed == False:
        raise ValueError("No such departure city.")

#ui
def start_app():
    print("Commands:\n"
          "1 -> add a new flight\n"
          "2 -> remove a flight\n"
          "3 -> display sorted flights by destination city\n"
          "4 -> change duration of all flights with the given departure city\n"
          "5 -> exit the app\n")
    flights = []
    while True:
        cmd = input("> ")

        match cmd:
            case "1":
                try:
                    code = input("Insert the code here: ")
                    duration = int(input("Insert the duration here: "))
                    dep_city = input("Insert the departure city here: ")
                    dest_city = input("Insert the destination city here: ")
                    add_flight(flights, [code, duration, dep_city, dest_city])
                    print("Added flight.\n")
                except ValueError as e:
                    print(str(e) + "\n")
            case "2":
                try:
                    code = input("Insert the code of the flight you want to delete here: ")
                    delete_flight(flights, code)
                    print(f"Removed flight with code {code}.\n")
                except ValueError as e:
                    print(str(e) + "\n")
            case "3":
                show_flights(flights)
                print("\n")
            case "4":
                try:
                    dep_city = input("Insert the departure city of the flights you want to change the duration to here: ")
                    new_duration = int(input("Insert the duration here: "))
                    change_duration(flights, dep_city, new_duration)
                    print("Changed duration for the flights.\n")
                except ValueError as e:
                    print(str(e) + "\n")
            case "5":
                print("Exiting...")
                return
            case _:
                print("Invalid command.\n")


def show_flights(flights:list) -> None:
    if len(flights) == 0:
        print("There are no flights right now.")
        return
    
    sorted_flights = sort_flights(flights)
    for flight in sorted_flights:
        print(f"Flight with code: {flight[0]}, duration: {flight[1]}, departure city: {flight[2]}, destination city: {flight[3]}")

start_app()