#include "tasks.h"

UTF8String::UTF8String(const char *str) {
    this->size = std::strlen(str);
    this->buffer = new Byte[this->size];
    std::copy(str, str + this->size, this->buffer);
}

UTF8String::UTF8String(const std::string &str) {
    this->size = str.size();
    this->buffer = new Byte[this->size];
    std::copy(str.begin(), str.end(), this->buffer);
}

UTF8String::UTF8String(const UTF8String &str) {
    this->size = str.size;
    this->buffer = new Byte[this->size];
    if (str.buffer != nullptr)
        std::copy(str.buffer, str.buffer + str.size, this->buffer);
}

UTF8String::UTF8String(UTF8String &&str) noexcept {
    this->size = str.size;
    this->buffer = str.buffer;
    str.buffer = nullptr;
}

UTF8String::UTF8String(size_t size, Byte *buffer) {
    this->size = size;
    this->buffer = new Byte[this->size];
    std::copy(buffer, buffer + size, this->buffer);
}

UTF8String &UTF8String::operator=(const UTF8String &str) {
    if (this != &str) {
        delete[] this->buffer;
        this->size = str.size;
        this->buffer = new Byte[this->size];
        std::copy(str.buffer, str.buffer + this->size, this->buffer);
    }
    return *this;
}

UTF8String &UTF8String::operator=(UTF8String &&str) noexcept {
    delete[] buffer;
    this->size = str.size;
    this->buffer = str.buffer;
    str.buffer = nullptr;
    return *this;
}

UTF8String::~UTF8String() {
    delete[] this->buffer;
}

UTF8String::UTF8String(const std::vector<CodePoint> &code_points) {
    this->size = 0;

    for (auto code_point: code_points) {
        this->size += static_cast<size_t>(get_point_byte_count(code_point));
    }

    this->buffer = new Byte[this->size];

    int i = 0;
    for (auto code_point: code_points) {
        encode_point(i, code_point);
    }
}

UTF8String UTF8String::operator+(const UTF8String &str) {
    // TODO ????
    auto new_size = this->size + str.size;
    auto new_buffer = new Byte[new_size];
    std::copy(this->buffer, this->buffer + this->size, new_buffer);
    std::copy(str.buffer, str.buffer + str.size, new_buffer + this->size);
    return UTF8String{new_size, new_buffer};
}

UTF8String &UTF8String::operator+=(const UTF8String &str) {
    auto new_size = this->size + str.size;
    auto new_buffer = new Byte[new_size];
    std::copy(this->buffer, this->buffer + this->size, new_buffer);
    std::copy(str.buffer, str.buffer + str.size, new_buffer + this->size);
    this->size = new_size;
    delete[] this->buffer;
    this->buffer = new_buffer;
    return *this;
}

bool UTF8String::operator==(const UTF8String &str) const {
    if (this->size != str.size)
        return false;
    for (size_t i = 0; i < this->size; i++) {
        if (this->buffer[i] != str[i].value())
            return false;
    }
    return true;
}

bool UTF8String::operator!=(const UTF8String &str) const {
    return !(*this == str);
}

bool UTF8String::operator==(const char *str) const {
    if (std::strlen(str) != this->size)
        return false;
    for (size_t i = 0; i < this->size; i++) {
        if (str[i] != this->buffer[i])
            return false;
    }
    return true;
}

bool operator==(const UTF8String &l, const char *r) {
    if (l.get_byte_count() != std::strlen(r))
        return false;
    for (size_t i = 0; i < l.get_byte_count(); i++) {
        if (l[i] != r[i])
            return false;
    }
    return true;
}

std::optional<Byte> UTF8String::operator[](size_t index) const {
    if (index >= this->size)
        return std::nullopt;
    return this->buffer[index];
}

UTF8String::operator std::string() const {
    return std::string{this->buffer, this->buffer + this->size};
}

void UTF8String::encode_point(int &i, const CodePoint &code_point) {
    if (get_point_byte_count(code_point) == 1)
        this->buffer[i++] = code_point;
    if (get_point_byte_count(code_point) == 2) {
        this->buffer[i++] = (code_point >> 6) | 0xC0;
        this->buffer[i++] = (code_point & 0x3F) | 0x80;
    }
    if (get_point_byte_count(code_point) == 3) {
        this->buffer[i++] = (code_point >> 12) | 0xE0;
        this->buffer[i++] = ((code_point >> 6) & 0x3F) | 0x80;
        this->buffer[i++] = (code_point & 0x3F) | 0x80;
    }
    if (get_point_byte_count(code_point) == 4) {
        this->buffer[i++] = (code_point >> 18) | 0xF0;
        this->buffer[i++] = ((code_point >> 12) & 0x3F) | 0x80;
        this->buffer[i++] = ((code_point >> 6) & 0x3F) | 0x80;
        this->buffer[i++] = (code_point & 0x3F) | 0x80;
    }
}

CodePoint UTF8String::decode_point(size_t &i) const {
    auto first = this->buffer[i++];
    if (get_point_byte_count(first) == 1)
        return first;
    if (get_point_byte_count(first) == 2) {
        auto second = this->buffer[i++];
        return ((first & 0x1F) << 6) | (second & 0x3F);
    }
    if (get_point_byte_count(first) == 3) {
        auto second = this->buffer[i++];
        auto third = this->buffer[i++];
        return ((first & 0x0F) << 12) | ((second & 0x3F) << 6) | (third & 0x3F);
    }
    if (get_point_byte_count(first) == 4) {
        auto second = this->buffer[i++];
        auto third = this->buffer[i++];
        auto fourth = this->buffer[i++];
        return ((first & 0x07) << 18) | ((second & 0x3F) << 12) | ((third & 0x3F) << 6) | (fourth & 0x3F);
    }
    return 0x00;
}

void UTF8String::append(CodePoint code_point) {
    auto code_point_len = get_point_byte_count(code_point);
    auto new_size = this->size + code_point_len;
    auto new_buffer = new Byte[new_size];
    std::copy(this->buffer, this->buffer + this->size, new_buffer);
    this->size = new_size;
    delete[] this->buffer;
    this->buffer = new_buffer;
    auto point_i = static_cast<int>(new_size - code_point_len);
    encode_point(point_i, code_point);
}

void UTF8String::append(char &&str) {
    auto new_size = this->size + 1;
    auto new_buffer = new Byte[new_size];
    std::copy(this->buffer, this->buffer + this->size, new_buffer);
    new_buffer[new_size - 1] = str;
    delete[] this->buffer;
    this->buffer = new_buffer;
    this->size = new_size;
}

size_t UTF8String::get_byte_count() const {
    return this->size;
}

int UTF8String::get_point_byte_count(Byte b) {
    if ((b >> 7) == 0b0)
        return 1;
    if ((b >> 5) == 0b110)
        return 2;
    if ((b >> 4) == 0b1110)
        return 3;
    if ((b >> 3) == 0b11110)
        return 4;
    return 0;
}

int UTF8String::get_point_byte_count(CodePoint cp) { // :3
    if (cp <= 0x7F)
        return 1;
    if (cp <= 0x7FF)
        return 2;
    if (cp <= 0xFFFF)
        return 3;
    if (cp <= 0x10FFFF)
        return 4;
    return 0;
}

int UTF8String::get_point_count() const {
    int point_count = 0;
    if (this->size == 0)
        return point_count;
    for (size_t i = 0; i < this->size; i++) {
        point_count++;
        i += get_point_byte_count(this->buffer[i]) - 1;
    }
    return point_count;
}

std::optional<CodePoint> UTF8String::nth_code_point(size_t index) const {
    if (index >= this->size)
        return std::nullopt;
    size_t i = 0;
    size_t point_count = 0;
    while (i < this->size) {
        if (point_count == index)
            return decode_point(i);
        i += get_point_byte_count(this->buffer[i]);
        point_count++;
    }
    return std::nullopt;
}
