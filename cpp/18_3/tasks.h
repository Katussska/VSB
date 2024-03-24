#pragma once

#include <memory>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>
#include <iostream>
#include <optional>
#include <cstring>
/// UTF-8 string (reuse your previous implementation and modify it)

using CodePoint = uint32_t;

class UTF8String {
private:
    std::vector<uint8_t> buffer;

public:
    class Iterator {
    private:
        uint8_t *current;
        const uint8_t *start;
        const uint8_t *finish;

    public:
        explicit Iterator(const uint8_t *begin, const uint8_t *end) : current(const_cast<uint8_t *>(begin)),
                                                                      start(begin), finish(end) {
        }

        explicit Iterator(uint8_t *curr, const uint8_t *begin, const uint8_t *end) : current(curr),
            start(begin), finish(end) {
        }

        Iterator begin();

        Iterator end();

        Iterator &operator++();

        Iterator &operator--();

        uint8_t &operator*() const;

        Iterator operator+=(int value);

        Iterator operator-=(int value);

        Iterator operator+(int value);

        Iterator operator-(int value);

        bool operator!=(const Iterator &other) const;

        bool operator==(const Iterator &other) const;
    };

    UTF8String() = default;

    explicit UTF8String(const char *str);

    explicit UTF8String(const std::string &str);

    static int byte_count_helper(uint8_t byte);

    [[nodiscard]] size_t get_byte_count() const;

    static int codepoint_count_helper(CodePoint codepoint);

    void encode(CodePoint code_point);

    [[nodiscard]] int get_point_count() const;

    explicit UTF8String(const std::vector<CodePoint> &);

    void append(CodePoint codepoint);

    UTF8String(const UTF8String &str);

    bool operator==(const UTF8String &str) const;

    bool operator!=(const UTF8String &str) const;

    std::optional<uint8_t> operator[](size_t index) const;

    [[nodiscard]] std::optional<CodePoint> nth_code_point(size_t index) const;

    explicit UTF8String(std::vector<uint8_t> bytes) : buffer(std::move(bytes)) {
    }

    UTF8String operator+(const UTF8String &str);

    UTF8String &operator+=(const UTF8String &str);

    explicit operator std::string() const;

    UTF8String(UTF8String &&str) noexcept: buffer(std::move(str.buffer)) {
    };

    UTF8String &operator=(const UTF8String &str);

    ~UTF8String() = default;

    [[nodiscard]] Iterator bytes() const;
};

/// Binary tree
// Big data that we cannot afford to copy
struct BigData {
    int value;

    explicit BigData(int value) : value(value) {
    }

    BigData(const BigData &) = delete;

    BigData &operator=(const BigData &) = delete;
};

class Tree {
private:
    std::shared_ptr<BigData> value;
    Tree *parent = nullptr;
    std::unique_ptr<Tree> left_child;
    std::unique_ptr<Tree> right_child;

public:
    class Iterator {
    private:
        Tree *current;

    public:
        explicit Iterator(const Tree *node) : current(const_cast<Tree *>(node)) {
        }

        Iterator &operator++();

        const Tree &operator*() const;

        bool operator!=(const Iterator &other) const;
    };

    explicit Tree(int n) : value(std::make_shared<BigData>(n)) {
    }

    explicit Tree(std::shared_ptr<BigData> val) : value(std::move(val)) {
    }

    [[nodiscard]] BigData &get_value() const;

    [[nodiscard]] Tree *get_parent() const;

    [[nodiscard]] bool has_parent() const;

    [[nodiscard]] Tree *get_left_child() const;

    [[nodiscard]] Tree *get_right_child() const;

    [[nodiscard]] Tree *get_root();

    std::unique_ptr<Tree> take_left_child();

    std::unique_ptr<Tree> take_right_child();

    std::unique_ptr<Tree> take_child(Tree &child);

    std::unique_ptr<Tree> set_left_child(std::unique_ptr<Tree> child);

    std::unique_ptr<Tree> set_right_child(std::unique_ptr<Tree> child);

    void swap_children();

    bool is_same_tree_as(Tree *other);

    void replace_value(const std::shared_ptr<BigData> &new_value);

    [[nodiscard]] Iterator begin() const;

    static Iterator end();
};
