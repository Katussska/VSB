#include "tasks.h"

#include <utility>

/// UTF-8
UTF8String::UTF8String(const char *str) {
    size_t size = std::strlen(str);
    buffer.reserve(size);
    std::copy(str, str + size, std::back_inserter(buffer));
}

UTF8String::UTF8String(const std::string &str) {
    size_t size = str.size();
    buffer.reserve(size);
    std::copy(str.begin(), str.end(), std::back_inserter(buffer));
}

size_t UTF8String::get_byte_count() const {
    return buffer.size();
}

int UTF8String::byte_count_helper(uint8_t byte) {
    if ((byte >> 7) == 0b0)
        return 1;
    if ((byte >> 5) == 0b110)
        return 2;
    if ((byte >> 4) == 0b1110)
        return 3;
    if ((byte >> 3) == 0b11110)
        return 4;
    return 0;
}

int UTF8String::get_point_count() const {
    int point_count = 0;

    if (buffer.empty())
        return point_count;

    for (size_t i = 0; i < buffer.size(); i++) {
        point_count++;
        if ((buffer.at(i) >> 7) == 0b0) {
            i += 0;
            continue;
        }

        if ((buffer.at(i) >> 5) == 0b110) {
            i += 1;
            continue;
        }

        if ((buffer.at(i) >> 4) == 0b1110) {
            i += 2;
            continue;
        }

        if ((buffer.at(i) >> 3) == 0b11110) {
            i += 3;
            continue;
        }
    }
    return point_count;
}

UTF8String::UTF8String(const std::vector<CodePoint> &cpvector) {
    size_t size = cpvector.size();
    buffer.reserve(size);

    for (auto codepoint: cpvector)
        append(codepoint);
}

int UTF8String::codepoint_count_helper(CodePoint codepoint) {
    if (codepoint <= 0x7F)
        return 1;
    if (codepoint <= 0x7FF)
        return 2;
    if (codepoint <= 0xFFFF)
        return 3;
    if (codepoint <= 0x10FFFF)
        return 4;
    return 0;
}

void UTF8String::encode(CodePoint code_point) {
    int byte_count = codepoint_count_helper(code_point);

    switch (byte_count) {
        case 1:
            buffer.push_back(code_point);
            break;
        case 2:
            buffer.push_back((code_point >> 6) | 0xC0);
            buffer.push_back((code_point & 0x3F) | 0x80);
            break;
        case 3:
            buffer.push_back((code_point >> 12) | 0xE0);
            buffer.push_back(((code_point >> 6) & 0x3F) | 0x80);
            buffer.push_back((code_point & 0x3F) | 0x80);
            break;
        case 4:
            buffer.push_back((code_point >> 18) | 0xF0);
            buffer.push_back(((code_point >> 12) & 0x3F) | 0x80);
            buffer.push_back(((code_point >> 6) & 0x3F) | 0x80);
            buffer.push_back((code_point & 0x3F) | 0x80);
            break;
        default:
            break;
    }
}

void UTF8String::append(CodePoint codepoint) {
    encode(codepoint);
}

UTF8String::UTF8String(const UTF8String &str) {
    if (!str.buffer.empty()) {
        buffer.reserve(str.buffer.size());
        std::copy(str.buffer.begin(), str.buffer.end(), std::back_inserter(buffer));
    }
}

bool UTF8String::operator==(const UTF8String &str) const {
    return std::equal(buffer.begin(), buffer.end(), str.buffer.begin(), str.buffer.end());
}

bool UTF8String::operator!=(const UTF8String &str) const {
    return !(std::equal(buffer.begin(), buffer.end(), str.buffer.begin(), str.buffer.end()));
}

std::optional<uint8_t> UTF8String::operator[](size_t index) const {
    if (index < buffer.size())
        return buffer.at(index);

    return std::nullopt;
}

std::optional<CodePoint> UTF8String::nth_code_point(size_t index) const {
    size_t i = 0;
    size_t pointCount = 0;
    while (i < buffer.size()) {
        auto byteCount = byte_count_helper(buffer.at(i));
        if (pointCount == index) {
            if (byteCount == 0)
                return std::nullopt;

            if (byteCount == 1)
                return buffer.at(i);

            CodePoint codePoint = buffer.at(i) & (0xFF >> (byteCount + 1));

            for (size_t j = 1; j < byteCount; ++j) {
                if (i + j >= buffer.size() || (buffer.at(i + j) & 0xC0) != 0x80)
                    return std::nullopt;
                codePoint = (codePoint << 6) | (buffer.at(i + j) & 0x3F);
            }
            return codePoint;
        }
        i += byteCount;
        ++pointCount;
    }
    return std::nullopt;
}

UTF8String UTF8String::operator+(const UTF8String &str) {
    UTF8String temp(this->buffer);

    for (auto byte: str.buffer)
        temp.buffer.push_back(byte);

    return temp;
}

UTF8String &UTF8String::operator+=(const UTF8String &str) {
    for (auto byte: str.buffer)
        buffer.push_back(byte);

    return *this;
}

UTF8String::operator std::string() const {
    return std::string(buffer.begin(), buffer.end());
}

UTF8String &UTF8String::operator=(const UTF8String &str) {
    if (this != &str) {
        buffer = std::vector<uint8_t>(str.buffer.size());
        std::copy(str.buffer.begin(), str.buffer.end(), buffer.begin());
    }

    return *this;
}

UTF8String::Iterator UTF8String::bytes() const {
    return Iterator(&buffer.front(), &buffer.back() + 1);
}

UTF8String::Iterator UTF8String::Iterator::begin() {
    current = const_cast<uint8_t *>(start);

    return *this;
}

UTF8String::Iterator UTF8String::Iterator::end() {
    current = const_cast<uint8_t *>(finish);

    return *this;
}

UTF8String::Iterator &UTF8String::Iterator::operator++() {
    if (current + 1 <= finish)
        current++;

    return *this;
}

UTF8String::Iterator &UTF8String::Iterator::operator--() {
    if (current - 1 >= start)
        current--;

    return *this;
}

uint8_t &UTF8String::Iterator::operator*() const {
    return *current;
}

UTF8String::Iterator UTF8String::Iterator::operator+=(int value) {
    if ((current + value) <= finish)
        current += value;

    return *this;
}

UTF8String::Iterator UTF8String::Iterator::operator-=(int value) {
    if ((current - value) >= start)
        current -= value;

    return *this;
}

UTF8String::Iterator UTF8String::Iterator::operator+(int value) {
    return Iterator(current + value, start, finish);
}

UTF8String::Iterator UTF8String::Iterator::operator-(int value) {
    return Iterator(current - value, start, finish);
}

bool UTF8String::Iterator::operator!=(const UTF8String::Iterator &other) const {
    return current != other.current;
}

bool UTF8String::Iterator::operator==(const UTF8String::Iterator &other) const {
    return current == other.current;
}


/// Binary tree
Tree::Iterator &Tree::Iterator::operator++() {
    if (!current) {
        return *this;
    }

    if (current->get_right_child()) {
        current = current->get_right_child();
        while (current->get_left_child()) {
            current = current->get_left_child();
        }
    } else {
        while (current->get_parent() && current->get_parent()->get_right_child() == current) {
            current = current->get_parent();
        }

        current = current->get_parent();
    }

    return *this;
}

const Tree &Tree::Iterator::operator*() const {
    return *current;
}

bool Tree::Iterator::operator!=(const Tree::Iterator &other) const {
    return current != other.current;
}

BigData &Tree::get_value() const {
    return *value;
}

Tree *Tree::get_parent() const {
    return parent;
}

bool Tree::has_parent() const {
    if (parent != nullptr)
        return true;
    else
        return false;
}

Tree *Tree::get_left_child() const {
    return left_child.get();
}

Tree *Tree::get_right_child() const {
    return right_child.get();
}

Tree *Tree::get_root() {
    if (!has_parent()) {
        return this;
    }

    Tree *current = this;

    while (current->has_parent()) {
        current = current->get_parent();
    }

    return current;
}

std::unique_ptr<Tree> Tree::take_left_child() {
    std::unique_ptr<Tree> taken = std::move(left_child);

    if (taken)
        taken->parent = nullptr;

    return taken;
}

std::unique_ptr<Tree> Tree::take_right_child() {
    std::unique_ptr<Tree> taken = std::move(right_child);

    if (taken)
        taken->parent = nullptr;

    return taken;
}

std::unique_ptr<Tree> Tree::take_child(Tree &child) {
    if (left_child && left_child.get() == &child) {
        std::unique_ptr<Tree> taken = std::move(left_child);
        taken->parent = nullptr;
        return taken;
    } else if (right_child && right_child.get() == &child) {
        std::unique_ptr<Tree> taken = std::move(right_child);
        taken->parent = nullptr;
        return taken;
    } else
        throw std::runtime_error("Not a child of the node.");
}

std::unique_ptr<Tree> Tree::set_left_child(std::unique_ptr<Tree> child) {
    std::unique_ptr<Tree> prev = std::move(left_child);
    left_child = std::move(child);

    if (left_child)
        left_child->parent = this;

    if (prev)
        prev->parent = nullptr;


    return prev;
}

std::unique_ptr<Tree> Tree::set_right_child(std::unique_ptr<Tree> child) {
    std::unique_ptr<Tree> prev = std::move(right_child);
    right_child = std::move(child);

    if (right_child)
        right_child->parent = this;

    if (prev)
        prev->parent = nullptr;


    return prev;
}

void Tree::swap_children() {
    std::swap(left_child, right_child);
}

bool Tree::is_same_tree_as(Tree *other) {
    // probably not workin correctly, but the implementation below should
    return get_root() == other->get_root();

    //        if (this->parent == nullptr && other->parent == nullptr) {
    //            if (this == other) { return true; }
    //            return false;
    //        }
    //
    //        if (this->parent == other->parent)
    //            return true;
    //
    //        if (this->parent != nullptr) {
    //            return parent->is_same_tree_as(other);
    //        } else if (other->parent != nullptr) {
    //            return other->parent->is_same_tree_as(this);
    //        }
    //
    //        return false;
}

void Tree::replace_value(const std::shared_ptr<BigData> &new_value) {
    value = new_value;

    if (left_child)
        left_child->replace_value(new_value);

    if (right_child)
        right_child->replace_value(new_value);
}

Tree::Iterator Tree::begin() const {
    Tree *leftmost = const_cast<Tree *>(this);

    while (leftmost->get_left_child())
        leftmost = leftmost->get_left_child();


    return Iterator(leftmost);
}

Tree::Iterator Tree::end() {
    return Iterator(nullptr);
}
