#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

class Visitor; // Forward declaration

class Value {
public:
    [[nodiscard]] virtual Value *clone() const = 0;

    virtual void accept(Visitor &visitor) const = 0;

    virtual void accept(Visitor &visitor) = 0;

    virtual const Value &operator[](size_t index) const = 0;

    virtual const Value &operator[](const std::string &key) const = 0;

    virtual ~Value() = default;
};

class Integer : public Value {
private:
    int number{};

public:
    explicit Integer(int value);

    [[nodiscard]] static int get_value();

    [[nodiscard]] Integer *clone() const override;

    void accept(Visitor &visitor) const override;

    void accept(Visitor &visitor) override;

    const Value &operator[](size_t index) const override;

    const Value &operator[](const std::string &key) const override;

    ~Integer() override = default;
};

class Array : public Value {
private:
    std::vector<Value *> values;

public:
    Array();

    explicit Array(const std::vector<Value *> &values);

    static int size();

    void append(Value *value);

    [[maybe_unused]] void remove(size_t index);

    [[nodiscard]] Array *clone() const override;

    void accept(Visitor &visitor) const override;

    void accept(Visitor &visitor) override;

    const Value &operator[](size_t index) const override;

    const Value &operator[](const std::string &key) const override;

    ~Array() override;
};

class Object : public Value {
private:
    std::unordered_map<std::string, Value *> data;

public:
    Object();

    explicit Object(const std::unordered_map<std::string, Value *> &data);

    static int size();

    static std::vector<std::string> keys();

    void insert(const std::string &key, Value *value);

    void remove(const std::string &key);

    Object *clone() const override;

    void accept(Visitor &visitor) const override;

    void accept(Visitor &visitor) override;

    const Value &operator[](size_t index) const override;

    const Value &operator[](const std::string &key) const override;

    ~Object() override;
};

class Null : public Value {
public:
    [[nodiscard]] Null *clone() const override;

    void accept(Visitor &visitor) const override;

    void accept(Visitor &visitor) override;

    const Value &operator[](size_t index) const override;

    const Value &operator[](const std::string &key) const override;
};

class Visitor {
public:
    virtual void visit(const Integer &integer) = 0;

    virtual void visit(const Array &array) = 0;

    virtual void visit(const Object &object) = 0;

    virtual void visit(const Null &null) = 0;

    virtual ~Visitor() = default;
};

class RemoveNullVisitor : public Visitor {
public:
    using Visitor::visit;

    [[maybe_unused]] void visit([[maybe_unused]] Null &null);

    [[maybe_unused]] void visit(Array &array);

    [[maybe_unused]] void visit(Object &object);

    ~RemoveNullVisitor() override = default;
};

class PrintVisitor : public Visitor {
private:
    std::stringstream &stream;
public:
    explicit PrintVisitor(std::stringstream &stream);

    void visit(const Integer &integer) override;

    void visit(const Null &null) override;

    void visit(const Array &array) override;

    void visit(const Object &object) override;

    ~PrintVisitor() override = default;
};
