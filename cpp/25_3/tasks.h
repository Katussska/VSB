#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <variant>
#include <map>
#include <optional>
#include <cctype>
#include <iomanip>
#include <cstring>

// JSON document: implement parsing.
// JSON is implemented using algebraic data types here, it should be more practical than working
// with the previous OOP hierarchy and pointers.
struct Boolean {
    bool value;

    bool operator==(const Boolean &other) const;
};

struct Number {
    double value;

    bool operator==(const Number &other) const;
};

struct Null {
    bool operator==(const Null &) const;
};

struct String {
    std::string value;

    bool operator==(const String &other) const;
};

struct Array;
struct Object;

using Value = std::variant<Boolean, Number, String, Null, Array, Object>;

struct Array {
    std::vector<Value> items;

    bool operator==(const Array &other) const;
};

struct Object {
    std::map<std::string, Value> items;

    bool operator==(const Object &other) const;

    [[nodiscard]] std::vector<std::string> keys() const {
        std::vector<std::string> keys;
        keys.reserve(this->items.size());
        for (const auto &key: this->items) {
            keys.push_back(key.first);
        }
        return keys;
    }
};

template<class... Ts>
struct overloaded : Ts ... {
    using Ts::operator()...;
};
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

std::optional<Value> parse_json(std::istream &is);

template<typename T>
std::optional<T> parse_specific_value(std::istream &is, const std::string &expected, const T &value);

std::optional<String> parse_string(std::istream &is);

std::optional<Array> parse_array(std::istream &is);

std::optional<Object> parse_object(std::istream &is);

std::optional<Boolean> parse_boolean(std::istream &is);

std::optional<Null> parse_null(std::istream &is);

std::optional<Number> parse_number(std::istream &is);

std::ostream &operator<<(std::ostream &os, const Value &value);

std::ostream &operator<<(std::ostream &os, const String &value);

std::ostream &operator<<(std::ostream &os, const Array &value);

std::ostream &operator<<(std::ostream &os, const Object &value);

std::ostream &operator<<(std::ostream &os, const Boolean &value);

std::ostream &operator<<(std::ostream &os, Null);

std::ostream &operator<<(std::ostream &os, const Number &value);

std::vector<uint8_t> serialize(const Value &value);

void serialize_boolean(const Boolean &b, std::vector<uint8_t> &serialized);

void serialize_number(const Number &num, std::vector<uint8_t> &serialized);

void serialize_string(const String &str, std::vector<uint8_t> &serialized);

void serialize_array(const Array &arr, std::vector<uint8_t> &serialized);

void serialize_object(const Object &obj, std::vector<uint8_t> &serialized);

Value deserialize(const std::vector<uint8_t> &serialized);

Value deserialize_value(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t>::const_iterator &end);

Value deserialize_bool(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t>::const_iterator &end);

Value deserialize_number(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t>::const_iterator &end);

Value deserialize_string(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t>::const_iterator &end);

Value deserialize_array(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t>::const_iterator &end);

Value deserialize_object(std::vector<uint8_t>::const_iterator &it, const std::vector<uint8_t>::const_iterator &end);
