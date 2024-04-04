#pragma once

#include <string>
#include <cstdint>
#include <functional>
#include <iostream>
#include <utility>
#include <cstring>
#include <optional>

using CodePoint = uint32_t;

class UTF8String {
private:
    uint8_t *data = nullptr; // Pointer to UTF-8 byte data
    size_t size = 0;   // Size of the string
    size_t reserved = 0; // Allocated memory


public:
    explicit UTF8String(char const *);

    explicit UTF8String(const std::vector<uint32_t> &codePoints);

    UTF8String(const UTF8String &str);

    UTF8String &operator=(const UTF8String &str);

    UTF8String &operator=(UTF8String &&str);


    int get_byte_count();

    int get_point_count();

    std::optional<uint8_t> operator[](size_t index) const;

    int32_t nth_code_point(std::vector<CodePoint>);


    UTF8String &append(size_t str);

    //  UTF8String &append(int32_t<CodePoint>);

    UTF8String &operator+(const UTF8String &str);

    UTF8String &operator+=(const UTF8String &str);

    UTF8String &operator==(const UTF8String &str);

    //  Can be converted to a std::string using an explicit cast.
    //  In this case, assume that the string contains only ASCII characters.

    ~UTF8String();
};
