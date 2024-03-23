#pragma once

#include <memory>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>
#include <iostream>

/// Binary tree
// Big data that we cannot afford to copy
struct BigData {
    int value;

    explicit BigData(int value) : value(value) {}

    BigData(const BigData &) = delete;

    BigData &operator=(const BigData &) = delete;
};

class Tree {
private:
    std::shared_ptr<BigData> value;
    Tree *parent = nullptr;
    std::unique_ptr<Tree> left_child;
    std::unique_ptr<Tree> right_child;
    bool visited = false;

public:
    class Iterator {
    private:
        Tree *current;
    public:
        explicit Iterator(const Tree *node) : current(const_cast<Tree *>(node)) {}

        Iterator &operator++();

        const Tree &operator*() const;

        bool operator!=(const Iterator &other) const;
    };

    explicit Tree(int n) : value(std::make_shared<BigData>(n)) {}

    explicit Tree(std::shared_ptr<BigData> val) : value(std::move(val)) {}

    [[nodiscard]] BigData &get_value() const;

    [[nodiscard]] Tree *get_parent() const;

    [[nodiscard]] bool has_parent() const;

    [[maybe_unused]] [[nodiscard]] bool get_visited() const;

    [[maybe_unused]] void set_visited(bool str);

    [[nodiscard]] Tree *get_left_child() const;

    [[nodiscard]] Tree *get_right_child() const;

    [[nodiscard]] Tree *get_root() const;

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

