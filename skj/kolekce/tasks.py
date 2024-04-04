from collections import defaultdict


def is_palindrome(data):
    """
    Returns True if `data` is a palindrome and False otherwise.
    Hint:
        slicing is your friend, use it
    Example:
        is_palindrome('aba') == True
        is_palindrome('abc') == False
    """
    if data == data[::-1]:
        return True
    else:
        return False


def lex_compare(a, b):
    """
    Lexicographically compare `a` with `b` and return the smaller string.
    Implement the comparison yourself, do not use the `<` operator for comparing strings :)

    Example:
        lex_compare('a', 'b') == 'a'
        lex_compare('ahoj', 'buvol') == 'ahoj'
        lex_compare('ahoj', 'ahojky') == 'ahoj'
        lex_compare('dum', 'automobil') == 'automobil'
    """
    minimum = min(len(a), len(b))

    for i in range(minimum):
        if a[i] != b[i]:
            return a if a[i] < b[i] else b

    return a if len(a) < len(b) else b


def count_successive(string):
    """
    Go through the string and for each character, count how many times it appears in succession.
    Store the character and the count in a tuple and return a list of such tuples.

    Example:
          count_successive("aaabbcccc") == [("a", 3), ("b", 2), ("c", 4)]
          count_successive("aba") == [("a", 1), ("b", 1), ("a", 1)]
    """
    if not string:
        return []

    result = []
    curr = string[0]
    count = 1

    for c in string[1:]:
        if c == curr:
            count += 1
        else:
            result.append((curr, count))
            curr = c
            count = 1

    result.append((curr, count))

    return result


def find_positions(items):
    """
    Go through the input list of items and collect indices of each individual item.
    Return a dictionary where the key will be an item and its value will be a list of indices
    where the item was found.

    Example:
        find_positions(["hello", 1, 1, 2, "hello", 2]) == {
            2: [3, 5],
            "hello": [0, 4],
            1: [1, 2]
        }
    """
    positions = defaultdict(list)
    for index, item in enumerate(items):
        positions[item].append(index)

    return dict(positions)


def invert_dictionary(dictionary):
    """
    Invert the input dictionary. Turn keys into values and vice-versa.
    If more values belonged to the same key, return None.

    Example:
        invert_dictionary({1: 2, 3: 4}) == {2: 1, 4: 3}
        invert_dictionary({1: 2, 3: 2}) is None
    """
    inverted = {}
    for key, value in dictionary.items():
        if value in inverted:
            return None
        else:
            inverted[value] = key

    return inverted
