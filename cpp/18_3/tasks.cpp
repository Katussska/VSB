#include "tasks.h"

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

[[maybe_unused]] bool Tree::get_visited() const {
    return visited;
}

[[maybe_unused]] void Tree::set_visited(bool str) {
    visited = str;
}

Tree *Tree::get_left_child() const {
    return left_child.get();
}

Tree *Tree::get_right_child() const {
    return right_child.get();
}

Tree *Tree::get_root() const {
    if (!has_parent()) {
        return const_cast<Tree *>(this);
    }

    Tree *current = const_cast<Tree *>(this);

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
