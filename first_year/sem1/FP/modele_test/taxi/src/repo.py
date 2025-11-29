from address import Address

class AddressRepo():
    def __init__(self):
        self.__data = []
        self.__load()

    def add(self, new_address:Address):
        for address in self.__data:
            if address.id == new_address.id:
                raise ValueError(f"Address with id {new_address.id} already exists.")

        self.__load()
        self.__data.append(new_address)
        self.__save()

    def list(self):
        self.__load()
        return self.__data

    def __load(self):
        self.__data.clear()
        with open("src/address.txt", "rt") as file:
            lines = file.readlines()
            for line in lines:
                tokens = line.split(',')
                self.__data.append(Address(int(tokens[0].strip()), tokens[1].strip(), int(tokens[2].strip()), int(tokens[3].strip()), int(tokens[4].strip().removesuffix("\n"))))

    def __save(self):
        with open("src/address.txt", "wt") as file:
            for line in self.__data:
                file.write(str(line) + '\n')