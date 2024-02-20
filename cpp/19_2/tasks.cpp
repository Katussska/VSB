#include "tasks.h"

// TODO: implement functions from assignment.md

namespace math {
    int fibonacci(int n) {
        if (n <= 0)
            return 0;
        else if (n == 1)
            return 1;
        else
            return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

namespace strutils {
    std::string camel_to_snake(std::string str) {
        std::string snake;

        for (long unsigned int i = 0; i < str.length(); ++i) {
            if (64 < str[i] && str[i] < 91) {
                if (!i == 0) {
                    snake += '_';
                }
                snake += tolower(str[i]);
                continue;
            }
            snake += str[i];
        }

        return snake;
    }

    bool parse_uint(std::string str, uint32_t &result) {
        int n = str.length();
        uint32_t temp = 0;

        if (n <= 0) {
            cout << "false" << endl;
            return false;
        }

        for (int i = 0; i < n; ++i) {
            if (!(47 < str[i] && str[i] < 58)) {
                cout << "false" << endl;
                return false;
            }

            if ((str[i] - 48) * std::pow(10, (n - i - 1)) >= 4294967295) {
                cout << "false" << endl;
                return false;
            }

            temp += (str[i] - 48) * std::pow(10, (n - i - 1));
        }

        if ((temp < str[0] - 48) * std::pow(10, (n - 1))) {
            cout << "false" << endl;
            return false;
        }
        result = temp;

        cout << "true, result == " << result << endl;
        return true;
    }

    bool validate_utf8(std::vector<uint8_t>, size_t result) {
        return false;
    }
}
