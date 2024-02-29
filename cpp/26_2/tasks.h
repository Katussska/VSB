#pragma once

#include <string>
#include <cstdint>
#include <functional>
#include <iostream>
#include <utility>
#include <cstring>

using CodePoint = uint32_t;

class UTF8String {
private:
    mutable char *buffer = nullptr;
    size_t size = 0;
    size_t reserved = 0;

public:
    UTF8String(std::string);

    UTF8String(std::vector<CodePoint>());

    UTF8String(const UTF8String &str);

    UTF8String &operator=(const UTF8String &str);

    UTF8String &operator=(UTF8String &&str);


    int get_byte_count();

    int get_point_count();

    char &operator[](const size_t str);

    char operator[](const size_t str) const;

    int32_t nth_code_point(std::vector<CodePoint>);


    UTF8String &append(const size_t str);

    //  UTF8String &append(int32_t<CodePoint>);

    UTF8String &operator+(const UTF8String &str);

    UTF8String &operator+=(const UTF8String &str);

    UTF8String &operator==(const UTF8String &str);

    //  Can be converted to an std::string using an explicit cast.
    //  In this case, assume that the string contains only ASCII characters.
};
