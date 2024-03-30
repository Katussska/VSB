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
    std::visit([&os](const auto &v) {
        os << v;
    }, value);
    return os;
}

std::ostream &operator<<(std::ostream &os, const String &value) {
    os << '"';

    for (char c: value.value) {
        if (c == '\\' || c == '"')
            os << '\\' << c;
        else if (std::isprint(static_cast<unsigned char>(c)))
            os << c;
        else {
            os << "\\u"
               << std::hex << std::setw(2) << std::setfill('0')
               << static_cast<int>(static_cast<unsigned char>(c));
        }
    }

    os << '"';

    return os;
}

std::ostream &operator<<(std::ostream &os, const Array &value) {
    os << "[";

    for (size_t i = 0; i < value.items.size(); ++i) {
        os << value.items[i];

        if (i != value.items.size() - 1) {
            os << ", ";
        }
    }

    os << "]";

    return os;
}

std::ostream &operator<<(std::ostream &os, const Object &value) {
    os << "{";

    size_t count = 0;
    for (const auto &[key, val]: value.items) {
        os << '"' << key << "\": " << val;

        if (++count < value.items.size())
            os << ", ";
    }

    os << "}";

    return os;
}

std::ostream &operator<<(std::ostream &os, const Boolean &value) {
    os << (value.value ? "true" : "false");
    return os;
}

std::ostream &operator<<(std::ostream &os, Null) {
    os << "null";
    return os;
}

std::ostream &operator<<(std::ostream &os, const Number &value) {
    os << value.value;
    return os;
}

std::vector<uint8_t> serialize(const Value &value) {
    std::vector<uint8_t> serialized;

    switch (value.index()) {
        case 0:
            serialized.push_back(1);
            serialize_boolean(std::get<Boolean>(value), serialized);
            break;
        case 1:
            serialized.push_back(2);
            serialize_number(std::get<Number>(value), serialized);
            break;
        case 2:
            serialized.push_back(3);
            serialize_string(std::get<String>(value), serialized);
            break;
        case 3:
            serialized.push_back(0);
            break;
        case 4:
            serialized.push_back(4);
            serialize_array(std::get<Array>(value), serialized);
            break;
        case 5:
            serialized.push_back(5);
            serialize_object(std::get<Object>(value), serialized);
            break;
    }

    return serialized;
}

void serialize_boolean(const Boolean &b, std::vector<uint8_t> &serialized) {
    serialized.push_back(static_cast<uint8_t>(b.value ? 1 : 0));
}

void serialize_number(const Number &num, std::vector<uint8_t> &serialized) {
    const auto *numData = reinterpret_cast<const uint8_t *>(&num.value);
    serialized.insert(serialized.end(), numData, numData + sizeof(double));
}

void serialize_string(const String &str, std::vector<uint8_t> &serialized) {
    size_t size = str.value.size();
    const auto *size_b = reinterpret_cast<const uint8_t *>(&size);

    serialized.insert(serialized.end(), size_b, size_b + sizeof(size_t));
    serialized.insert(serialized.end(), str.value.begin(), str.value.end());
}

void serialize_array(const Array &arr, std::vector<uint8_t> &serialized) {
    size_t size = arr.items.size();
    const auto size_b = reinterpret_cast<const uint8_t *>(&size);

    serialized.insert(serialized.end(), size_b, size_b + sizeof(size_t));

    for (const auto &item: arr.items) {
        std::vector<uint8_t> item_data = serialize(item);
        serialized.insert(serialized.end(), item_data.begin(), item_data.end());
    }
}

void serialize_object(const Object &obj, std::vector<uint8_t> &serialized) {
    size_t size = obj.items.size();
    const auto size_b = reinterpret_cast<const uint8_t *>(&size);

    serialized.insert(serialized.end(), size_b, size_b + sizeof(size_t));

    for (const auto &[key, item]: obj.items) {
        size_t size_k = key.size();
        const auto *size_b_k = reinterpret_cast<const uint8_t *>(&size_k);

        serialized.insert(serialized.end(), size_b_k, size_b_k + sizeof(size_t));
        serialized.insert(serialized.end(), key.begin(), key.end());

        std::vector<uint8_t> itemData = serialize(item);

        serialized.insert(serialized.end(), itemData.begin(), itemData.end());
    }
}

Value deserialize_value(uint8_t type, const std::vector<uint8_t> &data) {
    switch (type) {
        case 0:
            return Null();
        case 1:
            return deserialize_boolean(data);
        case 2:
            return deserialize_number(data);
        case 3:
            return deserialize_string(data);
        case 4:
            return deserialize_array(data);
        case 5:
            return deserialize_object(data);
        default:
            throw std::runtime_error("Unknown type.");
    }
}

Value deserialize(const std::vector<uint8_t> &serialized) {
    if (serialized.empty())
        throw std::runtime_error("Data empty.");


    uint8_t type = serialized[0];
    std::vector<uint8_t> data(serialized.begin() + 1, serialized.end());

    return deserialize_value(type, data);
}

Boolean deserialize_boolean(const std::vector<uint8_t> &data) {
    if (data.empty()) //just to be sure, i kdyz vim, ze na testy useless(i u ostatnich)
        throw std::runtime_error("Data missing");

    return data[0] == 1 ? Boolean{true} : Boolean{false};
}

Number deserialize_number(const std::vector<uint8_t> &data) {
    if (data.size() < sizeof(double))
        throw std::runtime_error("Data missing");

    double number;
    std::memcpy(&number, data.data(), sizeof(double));
    return Number{number};
}

String deserialize_string(const std::vector<uint8_t> &data) {
    if (data.size() < sizeof(size_t))
        throw std::runtime_error("Data missing.");

    size_t size;
    std::memcpy(&size, data.data(), sizeof(size_t));

    if (data.size() < sizeof(size_t) + size)
        throw std::runtime_error("String data incomplete.");

    std::string value(data.begin() + sizeof(size_t), data.begin() + sizeof(size_t) + size);

    return String{value};
}


Array deserialize_array(const std::vector<uint8_t> &data) {
    if (data.size() < sizeof(size_t))
        throw std::runtime_error("Array size data is incomplete");

    size_t arraySize;
    std::memcpy(&arraySize, data.data(), sizeof(size_t));
    size_t currentPos = sizeof(size_t);
    Array array;

    for (size_t i = 0; i < arraySize; ++i) {
        if (data.size() < currentPos + sizeof(uint8_t) + sizeof(size_t))
            throw std::runtime_error("Array type ID data is incomplete");

        uint8_t typeId = data[currentPos];
        size_t dataSize;

        std::memcpy(&dataSize, data.data() + currentPos + sizeof(uint8_t), sizeof(size_t));
        std::vector<uint8_t> valueData(data.begin() + currentPos + sizeof(uint8_t) + sizeof(size_t),
                                       data.begin() + currentPos + sizeof(uint8_t) + sizeof(size_t) + dataSize);
        array.items.push_back(deserialize_value(typeId, valueData));
        currentPos += sizeof(uint8_t) + sizeof(size_t) + dataSize;
    }
    return array;
}


Object deserialize_object(const std::vector<uint8_t> &data) {}