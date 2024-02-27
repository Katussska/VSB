def fizzbuzz(n):
    buzz = "Buzz"
    fizz = "Fizz"

    if n % 3 == 0 and n % 5 == 0:
        return fizz + buzz
    elif n % 3 == 0:
        return fizz
    elif n % 5 == 0:
        return buzz
    else:
        return n


def fibonacci(n):
    if n <= 0:
        return 0
    elif n == 1:
        return 1
    elif n == 2:
        return 1

    a, b = 1, 1
    count = 2

    while count < n:
        c = b
        b = a + b
        a = c
        count += 1

    return b


def dot_product(a, b):
    return sum(x * y for x, y in zip(a, b))


def redact(data, chars):
    for char in chars:
        data = data.replace(char, 'x')

    return data


def count_words(data):
    if len(data) == 0:
        return {}

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
    char = chr(cp)

    utf8 = char.encode('utf-8')

    return list(utf8)
