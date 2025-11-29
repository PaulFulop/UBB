
def add_festival(m_festivals:list, festival:list) -> None:
    """Adds a  festival.

    :param m_festivals: list of all festivals
    :type m_festivals: list
    :param festival: one festival to add
    :type festival: list
    :raises ValueError: the name of the festival is already there
    :raises ValueError: if the month is not a valid month
    """
    for m_festival in m_festivals:
        if m_festival[0] == festival[0]:
            raise ValueError("Invalid festival.")
        
    if festival[1] not in range(1, 13):
        raise ValueError("Invalid festival.")
    
    m_festivals.append(festival)

def string_key1(sublist:str) -> str:
    """for sorting based on festival name

    :param sublist: basically a fastival
    :type sublist: str
    :return: festival name
    :rtype: str
    """ 
    return sublist[0].lower()

def string_key2(sublist:str) -> int:
    """for sorting based on month

    :param sublist: basically a fastival
    :type sublist: str
    :return: festival month
    :rtype: int
    """
    return sublist[2]

def festivals_season(m_festivals:list, months:list) -> list:
    """creates a list of all the festivals during a certain season

    :param m_festivals: all the festivals
    :type m_festivals: list
    :param months: the months of the season
    :type months: list
    :raises ValueError: if there are no such festivals
    :return: the festivals with this property
    :rtype: list
    """
    m_festivals_sorted = sorted(m_festivals, key=string_key1)
    valid_festivals = []

    for month in months:
        for m_festival in m_festivals_sorted:
            if m_festival[1] == month:
                valid_festivals.append(m_festival)
    
    if len(valid_festivals) == 0:
        raise ValueError("No festival in this season.")
    
    return valid_festivals

def festivals_artist(m_festivals:list, artist:str) -> list:
    """creates a list of all the festivals with a certain artist

    :param m_festivals: all the festivals
    :type m_festivals: list
    :param artist: the name of the artist
    :type artist: str
    :raises ValueError: if there are no festivals that this artist will attend
    :return: the festivals with this property
    :rtype: list
    """
    m_festivals_sorted = sorted(m_festivals, key=string_key2)
    valid_festivals = []

    for m_festival in m_festivals_sorted:
        if artist in m_festival[3]:
            valid_festivals.append(m_festival)

    if len(valid_festivals) == 0:
        raise ValueError("No festival with this artist.")
    
    return valid_festivals


def display_festivals_season(m_festivals:list) -> None:
    months = ["january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"]
    for m_festival in m_festivals:
        print(f"{m_festival[0]} taking place during {months[m_festival[1]]} with the price of {m_festival[2]}. There will be: {m_festival[3]}.")

def display_destivals_artist(m_festivals:list, artist:str):
    months = ["january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"]
    print(f"For {artist} we have:\n")
    for m_festival in m_festivals: 
        print(f"{m_festival[0]}, taking place during {months[m_festival[1]]}, with the price of {m_festival[2]}.")

def start_app():
    m_festivals = [["Untold", 5, 500, ["Eminem", "Kanye"]], ["Electric castle", 8, 1000, ["Paul", "Sergiu"]], ["Coachella", 7, 250, ["Rammstein"]], ["Big concert", 10, 200, ["Eminem", "Paul"]], ["best singers", 2, 600, ["Paul", "Yeat"]], ["medieval songs", 5, 900, ["Yeat", "Sergiu"]]]
    print("Choose from the following:\n\n" + "1 -> add a festival\n" + "2 -> show festivals taking place during a season\n" + "3 -> show festivals where a given artist will perform\n" + "4 -> Exit the app\n")
    while True:
        choice = input("> ")

        match choice:
            case "1":
                try:
                    name = input("Type the name of the festival: ")
                    month = int(input("Type the month of the festival: "))
                    ticket = int(input("Type the cost of the festival: "))
                    artists = input("Type a list of artists (separated with ,): ").split(",")
                    add_festival(m_festivals, [name, month, ticket, artists])
                    print("Added festival.\n")
                except ValueError as e:
                    print(str(e) + "\n")
            case "2":
                season = input("Choose a season (winter, spring, summer, autumn): ").lower()
                match season:
                    case "winter":
                        try:
                            display_festivals_season(festivals_season(m_festivals, [12, 1, 2]))
                        except ValueError as e:
                            print(str(e) + '\n')
                    case "spring":
                        try:
                            display_festivals_season(festivals_season(m_festivals, [3, 4, 5]))
                        except ValueError as e:
                            print(str(e) + '\n')
                    case "summer":
                        try:
                            display_festivals_season(festivals_season(m_festivals, [6, 7, 8]))
                        except ValueError as e:
                            print(str(e) + '\n')
                    case "autumn":
                        try:
                            display_festivals_season(festivals_season(m_festivals, [9, 10, 11]))
                        except ValueError as e:
                            print(str(e) + '\n')
                    case _:
                        print("Invalid season.\n")
            case "3":
                artist = input("Type the name of an artist: ")
                try:
                    display_destivals_artist(festivals_artist(m_festivals, artist), artist)
                except ValueError as e:
                        print(str(e) + '\n')
            case "4":
                print("Exiting the app...")
                return
            case _:
                print("Invalid choice.\n")

start_app()