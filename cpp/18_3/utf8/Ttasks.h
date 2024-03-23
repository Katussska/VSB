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

        Iterator &operator++() {
            if (!current) {
                return *this;
            }

            // If the current node has a right child, go to the leftmost node of its right subtree
            if (current->get_right_child()) {
                current = current->get_right_child();
                while (current->get_left_child()) {
                    current = current->get_left_child();
                }
            } else {
                // Otherwise, move up the tree until we find a parent whose left child is the current node
                while (current->get_parent() && current->get_parent()->get_right_child() == current) {
                    current = current->get_parent();
                }
                // Move to the parent if it exists
                current = current->get_parent();
            }

            return *this;
        }


        const Tree &operator*() const {
            return *current;
        }

        bool operator!=(const Iterator &other) const {
            return current != other.current;
        }
    };

    explicit Tree(int n) : value(std::make_shared<BigData>(n)) {}

    explicit Tree(std::shared_ptr<BigData> val) : value(std::move(val)) {}

    [[nodiscard]] BigData &get_value() const {
        return *value;
    }

    [[nodiscard]] Tree *get_parent() const {
        return parent;
    }

    [[nodiscard]] bool has_parent() const {
        if (parent != nullptr)
            return true;
        else
            return false;
    }

    [[nodiscard]] bool get_visited() const {
        return visited;
    }

    void set_visited(bool str) {
        visited = str;
    }

    [[nodiscard]] Tree *get_left_child() const {
        return left_child.get();
    }

    [[nodiscard]] Tree *get_right_child() const {
        return right_child.get();
    }

    [[nodiscard]] Tree *get_root() const {
        if (!has_parent()) {
            return const_cast<Tree *>(this);
        }

        Tree *current = const_cast<Tree *>(this);

        while (current->has_parent()) {
            current = current->get_parent();
        }

        return current;
    }

    std::unique_ptr<Tree> take_left_child() {
        std::unique_ptr<Tree> taken = std::move(left_child);

        if (taken)
            taken->parent = nullptr;

        return taken;
    }

    std::unique_ptr<Tree> take_right_child() {
        std::unique_ptr<Tree> taken = std::move(right_child);

        if (taken)
            taken->parent = nullptr;

        return taken;
    }

    std::unique_ptr<Tree> take_child(Tree &child) {
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

    std::unique_ptr<Tree> set_left_child(std::unique_ptr<Tree> child) {
        std::unique_ptr<Tree> prev = std::move(left_child);
        left_child = std::move(child);

        if (left_child)
            left_child->parent = this;

        if (prev)
            prev->parent = nullptr;  // Set the parent of prev to null


        return prev;
    }

    std::unique_ptr<Tree> set_right_child(std::unique_ptr<Tree> child) {
        std::unique_ptr<Tree> prev = std::move(right_child);
        right_child = std::move(child);

        if (right_child)
            right_child->parent = this;

        if (prev)
            prev->parent = nullptr;  // Set the parent of prev to null


        return prev;
    }

    void swap_children() {
        std::swap(left_child, right_child);
    }

//  Prochazi mi jak jednoradkove, tak to vice xd takze idk
    bool is_same_tree_as(Tree *other) {
        return get_root() == other->get_root();

//        if (this->parent == nullptr && other->parent == nullptr) {
//            if (this == other) { return true; }
//            return false;
//        }
//
//        if (this->parent == other->parent) {
//            return true;
//        }
//
//        if (this->parent != nullptr) {
//            return parent->is_same_tree_as(other);
//        } else if (other->parent != nullptr) {
//            return other->parent->is_same_tree_as(this);
//        }
//
//        return false;
    }

    void replace_value(const std::shared_ptr<BigData> &new_value) {
        value = new_value;

        if (left_child)
            left_child->replace_value(new_value);

        if (right_child)
            right_child->replace_value(new_value);
    }

    [[nodiscard]] Iterator begin() const {
        Tree *leftmost = const_cast<Tree *>(this);

        while (leftmost->get_left_child()) {
            leftmost = leftmost->get_left_child();
        }

        return Iterator(leftmost);
    }

    [[nodiscard]] static Iterator end() {
        return Iterator(nullptr);
    }
};

