#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

class Visitor; // Forward declaration

class Value {
public:
    [[nodiscard]] virtual Value *clone() const = 0;

    virtual void accept(const Visitor &visitor) = 0;

    virtual Value *operator[](size_t index) const = 0;

    virtual Value *operator[](const std::string &key) const = 0;

    virtual ~Value() = default;
};

class Integer : public Value {
private:
    int number;

public:
    explicit Integer(int value);

    [[nodiscard]] int get_value() const;

    [[nodiscard]] Integer *clone() const override;

    void accept(const Visitor &visitor) override;

    Value *operator[](size_t index) const override;

    Value *operator[](const std::string &key) const override;

    ~Integer() override = default;
};

class Array : public Value {
public:
    std::vector<Value *> values;

    Array() = default;

    explicit Array(const std::vector<Value *> &values);

    [[nodiscard]] size_t size() const;

    void append(Value *value);

    [[maybe_unused]] void remove(int index);

    [[nodiscard]] Array *clone() const override;

    void accept(const Visitor &visitor) override;

    Value *operator[](size_t index) const override;

    Value *operator[](const std::string &key) const override;

    ~Array() override = default;
};

class Object : public Value {
public:
    std::unordered_map<std::string, Value *> data;

    Object() = default;

    explicit Object(const std::unordered_map<std::string, Value *> &pair);

    [[nodiscard]] size_t size() const;

    [[nodiscard]] std::vector<std::string> keys() const;

    void insert(const std::string &key, Value *value);

    [[maybe_unused]]  void remove(const std::string &key);

    [[nodiscard]] Object *clone() const override;

    void accept(const Visitor &visitor) override;

    Value *operator[](size_t index) const override;

    Value *operator[](const std::string &key) const override;

    ~Object() override = default;
};

class Null : public Value {
public:
    [[nodiscard]] Null *clone() const override;

    void accept(const Visitor &visitor) override;

    Value *operator[](size_t index) const override;

    Value *operator[](const std::string &key) const override;
};

class Visitor {
public:
    virtual void visit(Integer &integer) const = 0;

    [[maybe_unused]] virtual void visit(Null &null) const = 0;

    [[maybe_unused]] virtual void visit(Object &object) const = 0;

    [[maybe_unused]] virtual void visit(Array &array) const = 0;

    virtual ~Visitor() = default;
};

class RemoveNullVisitor : public Visitor {
public:
    RemoveNullVisitor() = default;

    void visit(Integer &integer) const override {};

    void visit(Null &null) const override {};

    void visit(Array &array) const override;

    void visit(Object &object) const override;

    ~RemoveNullVisitor() override = default;

};

class PrintVisitor : public Visitor {
private:
    std::stringstream &stream;
public:
    explicit PrintVisitor(std::stringstream &stream);

    void visit(Integer &integer) const override;

    void visit(Null &null) const override;

    void visit(Array &array) const override;

    void visit(Object &object) const override;

    ~PrintVisitor() override = default;

};
