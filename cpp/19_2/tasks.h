#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <complex>

using std::cout;
using std::endl;

namespace math {
    int fibonacci(int n);
}

namespace strutils {
    std::string camel_to_snake(std::string str);

    bool parse_uint(std::string str, uint32_t &result);

    bool validate_utf8(std::vector<uint8_t>, size_t result);
}