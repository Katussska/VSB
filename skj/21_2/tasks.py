def fizzbuzz(n):
    for i in range(1, n + 1):
        if i % 3 == 0 and i % 5 == 0:
            print("FizzBuzz")
        elif i % 3 == 0:
            print("Fizz")
        elif i % 5 == 0:
            print("Buzz")
        else:
            print(i)


def fibonacci(n):
    fibb = [0, 1]

    while fibb[-1] + fibb[-2] <= n:
        fibb.append(fibb[-1] + fibb[-2])

    return fibb


def dot_product(a, b):
    return sum(x * y for x, y in zip(a, b))


def redact(data, chars):
    for char in chars:
        data = data.replace(char, 'x')

    return data


def count_words(data):
    counter = {}
    words = data.split(" ")

    for word in words:
        if word in counter:
            counter[word] += 1
        else:
            counter[word] = 1

    return counter


def bonus_fizzbuzz(n):
    result = "Fizz" * (n % 3 == 0) + "Buzz" * (n % 5 == 0)
    return result or n


def bonus_utf8(cp):
    """
    Encode `cp` (a Unicode code point) into 1-4 UTF-8 bytes - you should know this from `Základy číslicových systémů (ZDS)`.
    Example:
        bonus_utf8(0x01) == [0x01]
        bonus_utf8(0x1F601) == [0xF0, 0x9F, 0x98, 0x81]
    """
    pass
