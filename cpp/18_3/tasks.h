#pragma once

#include <memory>
#include <cstdint>
#include <utility>

/// UTF-8 string (reuse your previous implementation and modify it)

using CodePoint = uint32_t;
class UTF8String;

/// Binary tree
// Big data that we cannot afford to copy
struct BigData {
    explicit BigData(int value): value(value) {}

    BigData(const BigData&) = delete;
    BigData& operator=(const BigData&) = delete;

    bool operator==(int n) const{
        return  value ==n;
    }
    BigData &operator=(int n){
        value = n; return *this;
    }

    int value;
};

class Tree{
public:
    struct Node : std::enable_shared_from_this<Node>{
    public:
        std::shared_ptr<BigData> value;
        std::unique_ptr<Node> left_child = nullptr;
        std::unique_ptr<Node> right_child = nullptr;
        std::shared_ptr<Node> parent = nullptr;

        Node(std::shared_ptr<BigData> data,std::shared_ptr<Node> par ) : value(std::move(data)), parent(std::move(par)){}
    };

    std::shared_ptr<BigData> value;
    std::unique_ptr<Node> root = nullptr;

    Tree() : value(nullptr) {}
    explicit Tree(std::shared_ptr<BigData> n) : value(std::move(n)){}
    explicit Tree(std::unique_ptr<BigData> n) : value(std::move(n)){}

    [[nodiscard]] std::shared_ptr<BigData> get_value() const{
        return value;
    }
    [[nodiscard]] Tree* get_root() const{
        return reinterpret_cast<Tree *>(root.get());
    }
    [[nodiscard]] Tree* get_parent() const{
        root->parent.get();
    }
    [[nodiscard]] Tree* get_left_child() const{
        return reinterpret_cast<Tree *>(root->left_child.get());
    }
    [[nodiscard]] Tree* get_right_child() const{
        return reinterpret_cast<Tree *>(root->right_child.get());
    }

    Tree* set_left_child(std::unique_ptr<Tree>(t)){
        std::unique_ptr<Node> previous_child = std::move(root->left_child);
        root->left_child = std::make_unique<Node>(std::move(t), root->shared_from_this());
        return this;
    }
    Tree* set_right_child(std::unique_ptr<Tree>(t)){
        std::unique_ptr<Node> previous_child = std::move(root->right_child);
        root->right_child = std::make_unique<Node>(std::move(t), root->shared_from_this());
        return this;
    }

    [[nodiscard]] bool has_parent() const{
        return root->parent != nullptr;
    }
    bool is_same_tree_as(Tree* other){
        return this == other;
    }

    void take_child(Tree&);
    void take_left_child();
    void take_right_child();
    void swap_children();
    void replace_value(std::shared_ptr<BigData> data);

};
