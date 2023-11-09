#include <iostream>
#include <list>

template <typename T>
class HashTable {
private:
    int size;
    std::list<std::pair<int, T>>* table;

public:
    HashTable(int size) {
        this->size = size;
        table = new std::list<std::pair<int, T>>[size];
    }

    void insert(int key, T value) {
        int index = key % size;
        table[index].push_back(std::make_pair(key, value));
    }

    T search(int key) {
        int index = key % size;
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return nullptr;
    }

    bool remove(int key) {
        int index = key % size;
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }

    void printWithContents() {
        for (int i = 0; i < size; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& pair : table[i]) {
                std::cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            std::cout << std::endl;
        }
    }

    ~HashTable() {
        delete[] table;
    }
};

int main() {
    const char* numberWords[] = {
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
            "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
            "seventeen", "eighteen", "nineteen", "twenty",
            "twenty-one", "twenty-two", "twenty-three", "twenty-four", "twenty-five",
            "twenty-six", "twenty-seven", "twenty-eight", "twenty-nine",
            "thirty", "thirty-one", "thirty-two", "thirty-three", "thirty-four", "thirty-five",
            "thirty-six", "thirty-seven", "thirty-eight", "thirty-nine",
            "forty", "forty-one", "forty-two", "forty-three", "forty-four", "forty-five",
            "forty-six", "forty-seven", "forty-eight", "forty-nine",
            "fifty", "fifty-one", "fifty-two", "fifty-three", "fifty-four", "fifty-five",
            "fifty-six", "fifty-seven", "fifty-eight", "fifty-nine",
            "sixty", "sixty-one", "sixty-two", "sixty-three", "sixty-four", "sixty-five",
            "sixty-six", "sixty-seven", "sixty-eight", "sixty-nine",
            "seventy", "seventy-one", "seventy-two", "seventy-three", "seventy-four", "seventy-five",
            "seventy-six", "seventy-seven", "seventy-eight", "seventy-nine",
            "eighty", "eighty-one", "eighty-two", "eighty-three", "eighty-four", "eighty-five",
            "eighty-six", "eighty-seven", "eighty-eight", "eighty-nine",
            "ninety", "ninety-one", "ninety-two", "ninety-three", "ninety-four", "ninety-five",
            "ninety-six", "ninety-seven", "ninety-eight", "ninety-nine", "one hundred"
    };

    int size = 10;

    HashTable<const char*> ht(size);

    for (int i = 0; i < 100; ++i) {
        ht.insert(i, numberWords[i]);
    }

    ht.printWithContents();

    return 0;
}
