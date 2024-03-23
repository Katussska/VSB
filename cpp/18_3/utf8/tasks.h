#pragma once

#include <string>
#include <cstdint>
#include <functional>
#include <iostream>
#include <utility>
#include <cstring>
#include <algorithm>
#include <iterator>
#include <optional>

using CodePoint = uint32_t;
using Byte = uint8_t;

class UTF8String {
private:
    Byte *buffer = nullptr;
    size_t size = 0;

    static int get_point_byte_count(Byte b);

    static int get_point_byte_count(CodePoint cp);

    void encode_point(int &i, const CodePoint &code_point);

    CodePoint decode_point(size_t &i) const;

public:

    UTF8String() = default;

    explicit UTF8String(const char *str);

    explicit UTF8String(const std::string &str);

    UTF8String(const UTF8String &str);

    UTF8String(UTF8String &&str) noexcept;

    UTF8String(size_t size, Byte *buffer);

    explicit UTF8String(const std::vector<CodePoint> &code_points);

    ~UTF8String();

    UTF8String &operator=(const UTF8String &str);

    UTF8String &operator=(UTF8String &&str) noexcept;

    UTF8String operator+(const UTF8String &str);

    UTF8String &operator+=(const UTF8String &str);

    bool operator==(const UTF8String &str) const;

    bool operator!=(const UTF8String &str) const;

    bool operator==(const char *str) const;

    friend bool operator==(const UTF8String &l, const char *r);

    std::optional<Byte> operator[](size_t index) const;

    explicit operator std::string() const;

    void append(CodePoint code_point);

    void append(char &&str);

    size_t get_byte_count() const;

    int get_point_count() const;

    std::optional<CodePoint> nth_code_point(size_t index) const;

};
