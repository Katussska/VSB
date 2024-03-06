#include "tasks.h"

UTF8String::UTF8String(const char *str) {
    size = strlen(str);

    data = new uint8_t[size + 1];

    int byteIndex = 0;
    for (size_t i = 0; i < size; ++i) {
        auto byte = static_cast<uint8_t>(str[i]);
        data[byteIndex++] = byte;
    }

    reserved = size + 1;
}

UTF8String::UTF8String(const std::vector<uint32_t> &codePoints) {
    size_t byteCount = 0;

    // Výpočet počtu bytů potřebných pro kódování všech kódových bodů
    for (uint32_t codePoint: codePoints) {
        if (codePoint <= 0x7F) {
            byteCount += 1;
        } else if (codePoint <= 0x7FF) {
            byteCount += 2;
        } else if (codePoint <= 0xFFFF) {
            byteCount += 3;
        } else if (codePoint <= 0x10FFFF) {
            byteCount += 4;
        }
    }

    // Alokace paměti pro UTF-8 byty
    data = new uint8_t[byteCount];

    size_t byteIndex = 0;
    for (uint32_t codePoint: codePoints) {
        if (codePoint <= 0x7F) {
            data[byteIndex++] = static_cast<uint8_t>(codePoint);
        } else if (codePoint <= 0x7FF) {
            data[byteIndex++] = static_cast<uint8_t>((codePoint >> 6) | 0xC0);
            data[byteIndex++] = static_cast<uint8_t>((codePoint & 0x3F) | 0x80);
        } else if (codePoint <= 0xFFFF) {
            data[byteIndex++] = static_cast<uint8_t>((codePoint >> 12) | 0xE0);
            data[byteIndex++] = static_cast<uint8_t>(((codePoint >> 6) & 0x3F) | 0x80);
            data[byteIndex++] = static_cast<uint8_t>((codePoint & 0x3F) | 0x80);
        } else if (codePoint <= 0x10FFFF) {
            data[byteIndex++] = static_cast<uint8_t>((codePoint >> 18) | 0xF0);
            data[byteIndex++] = static_cast<uint8_t>(((codePoint >> 12) & 0x3F) | 0x80);
            data[byteIndex++] = static_cast<uint8_t>(((codePoint >> 6) & 0x3F) | 0x80);
            data[byteIndex++] = static_cast<uint8_t>((codePoint & 0x3F) | 0x80);
        }
    }

    size = byteIndex;
    reserved = size + 1;
}

UTF8String::~UTF8String() {
    if (data != nullptr)
        delete[] data;
}

UTF8String::UTF8String(const UTF8String &str) {

}

UTF8String &UTF8String::operator=(const UTF8String &str) {

}

UTF8String &UTF8String::operator=(UTF8String &&str) {

}

int UTF8String::get_byte_count() {
    return 0;
}

int UTF8String::get_point_count() {
    return 0;
}

std::optional<uint8_t> UTF8String::operator[](size_t index) const {
    if (index >= size) {
        return std::nullopt;
    }

    return data[index];
}

int32_t UTF8String::nth_code_point(std::vector<CodePoint>) {
    return 0;
}

UTF8String &UTF8String::append(const size_t str) {

}

UTF8String &UTF8String::operator+(const UTF8String &str) {

}

UTF8String &UTF8String::operator+=(const UTF8String &str) {

}

UTF8String &UTF8String::operator==(const UTF8String &str) {

}
