from ui import menu

def start_app():
    coffees = [["Caffe miel", "France", 10], ["Cappucino", "Italy", 8.7], ["Frappucino", "Belgium", 5.65]]
    menu(coffees)

if __name__ == "__main__":
    start_app()