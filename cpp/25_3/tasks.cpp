#include "tasks.h"

bool Array::operator==(const Array &other) const {
    return other.items == this->items;
}

bool Object::operator==(const Object &other) const {
    return other.items == this->items;
}

bool String::operator==(const String &other) const {
    return other.value == this->value;
}

bool Null::operator==(const Null &) const {
    return true;
}

bool Number::operator==(const Number &other) const {
    return other.value == this->value;
}

bool Boolean::operator==(const Boolean &other) const {
    return other.value == this->value;
}

std::optional<Value> parse_json(std::istream &is) {
    is >> std::ws;

    auto first = is.peek();

    switch (first) {
        case '"':
            return parse_string(is);
        case '[':
            return parse_array(is);
        case '{':
            return parse_object(is);
        case 'f':
            return parse_boolean(is);
        case 'n':
            return parse_null(is);
        case 't':
            return parse_boolean(is);
        default:
            if (isdigit(first) || first == '-')
                return parse_number(is);
            else
                return std::nullopt;
    }
}

template<typename T>
std::optional<T> parse_specific_value(std::istream &is, const std::string &expected, const T &value) {
    std::string from_istream;
    from_istream.resize(expected.size());

    is.read(&from_istream[0], expected.size());

    if (from_istream == expected)
        return value;
    else
        return std::nullopt;
}

std::optional<String> parse_string(std::istream &is) {
    is.get();

    std::string decoded;
    char current;

    while (is.get(current)) {
        if (current == '"')
            return String{value: decoded};
        else if (current == '\\') {
            if (!is.get(current))
                return std::nullopt;
            switch (current) {
                case '\\':
                case '"':
                    decoded.push_back(current);
                    break;
                default:
                    return std::nullopt;
            }
        } else
            decoded.push_back(current);
    }

    return std::nullopt;
}

std::optional<Array> parse_array(std::istream &is) {
    Array array;
    char current;

    is.get();

    while (is.peek() != ']') {
        is >> std::ws;
        if (is.peek() == ']')
            return array;

        std::optional<Value> value = parse_json(is);

        if (!value.has_value())
            return std::nullopt;

        array.items.push_back(*value);

        is >> std::ws;

        if (is.peek() == ',') {
            is.get(current);
            if (is.peek() == ']')
                return std::nullopt;
        } else if (is.peek() != ']')
            return std::nullopt;
    }

    is.get(current);

    return array;
}

std::optional<Object> parse_object(std::istream &is) {
    Object object;
    char current;

    is.get();
    is >> std::ws;

    while (is.peek() != '}') {
        std::optional<Value> key = parse_json(is);

        if (!key || !std::holds_alternative<String>(*key))
            return std::nullopt;

        is >> std::ws;

        if (is.peek() != ':')
            return std::nullopt;

        is.get();
        is >> std::ws;

        std::optional<Value> value = parse_json(is);

        if (!value)
            return std::nullopt;

        is >> std::ws;

        object.items[std::get<String>(*key).value] = *value;

        if (is.peek() == ',') {
            is.get();

            if (is.peek() == '}')
                return std::nullopt;
        }

        is >> std::ws;
    }

    if (is.get(current) && current != '}')
        return std::nullopt;

    return object;
}

std::optional<Boolean> parse_boolean(std::istream &is) {
    const std::string trueValue = "true";
    const std::string falseValue = "false";

    if (is.peek() == 't') {
        return parse_specific_value<Boolean>(is, trueValue, Boolean{true});
    } else if (is.peek() == 'f') {
        return parse_specific_value<Boolean>(is, falseValue, Boolean{false});
    } else {
        return std::nullopt;
    }
}

std::optional<Null> parse_null(std::istream &is) {
    const std::string nullValue = "null";
    return parse_specific_value<Null>(is, nullValue, Null());
}

std::optional<Number> parse_number(std::istream &is) {
    std::string decoded;
    char current;

    is.get(current);
    decoded.push_back(current);

    if (current == '-') {
        is.get(current);
        decoded.push_back(current);
    }

    while (isdigit(is.peek()) || is.peek() == '.') {
        is.get(current);
        if (current == '.')
            if (!isdigit(is.peek()))
                break;
        decoded.push_back(current);
    }

    if (decoded.empty())
        return std::nullopt;

    try {
        double value = std::stod(decoded);
        return Number{value: value};
    } catch (...) {
        return std::nullopt;
    }
}

std::ostream &operator<<(std::ostream &os, const Value &value) {

}

std::ostream &operator<<(std::ostream &os, const String &value) {}

std::ostream &operator<<(std::ostream &os, const Array &value) {}

std::ostream &operator<<(std::ostream &os, const Object &value) {}

std::ostream &operator<<(std::ostream &os, const Boolean &value) {}

std::ostream &operator<<(std::ostream &os, Null) {}

std::ostream &operator<<(std::ostream &os, const Number &value) {}

std::vector<uint8_t> serialize(const Value &value) {
    return {};
}

Value deserialize(const std::vector<uint8_t> &data) {
    return Null();
}

