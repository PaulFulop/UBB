import random as rand

def generate_number() -> int:
    digits = list(range(1, 9))

    first_digit = rand.choice(digits)
    digits.remove(first_digit)
    digits.append(0)

    second_digit = rand.choice(digits)
    digits.remove(second_digit)

    third_digit = rand.choice(digits)
    digits.remove(third_digit)

    fourth_digit = rand.choice(digits)
    digits.remove(fourth_digit)

    return 1000 * first_digit + 100 * second_digit + 10 * third_digit + fourth_digit

def valid_len(n:int) -> bool:
    cnt = 0
    while n != 0:
        cnt += 1
        n //=10

    if cnt == 4:
        return True
    return False

def distinct_digits(n:int) -> bool:
    digits = []
    while n != 0:
        digits.append(n % 10)
        n //= 10
    
    setd = set(digits)
    if len(digits) == len(setd):
        return True
    return False

def codes(secret_num:int, num:int) -> list:
    if num == 0:
        return []
    
    if num % 10 == secret_num % 10:
        return codes(secret_num // 10, num // 10) + [num % 10]
    
    return codes(secret_num // 10, num // 10)

def runners(secret_num:int, num:int) -> int:
    secret_digits, digits = [], []
    cnt = 0

    while num != 0:
        secret_digits.append(secret_num % 10)
        digits.append(num % 10)
        secret_num //= 10
        num //= 10

    for i in range(4):
        for j in range(4):
            if i != j and secret_digits[i] == digits[j]:
                cnt += 1
    
    return cnt

def start_game() -> None:
    while True:
        print("Choose options:\n" + "1 -> start new game\n" + "2 -> exit game\n")
        choice = input("> ")
        if choice == "1":
            secret_num = generate_number()
            print("The computer generated a secret random number with 4 distinct digits.\n" + "Insert a valid number and try to find it:\n")

            while True:
                num = input("> ")
                if num[0] == "0":
                    print("Game over!\n")
                else:
                    try:
                        num = int(num)
                        if num == 8086:
                            print(f"The secret number is {secret_num}.\n")
                        elif valid_len(num) and distinct_digits(num):
                            if num == secret_num:
                                print("You won!\n")
                                break
                            print(f"You have {len(codes(secret_num, num))} codes and {runners(secret_num, num)} runners. Try again.\n")
                        elif not valid_len(num) or not distinct_digits(num):
                            print("Game over!\n")
                            break 
                    except ValueError as e:
                        print(str(e))
                        break
        elif choice == "2":
            return
        else:
            print("Invalid choice.\n")

start_game()