#pragma once

#include <vector>
#include <unordered_map>
#include <string>

class Value {
};

class Integer : public Value {
private:
    int number{};

public:
    explicit Integer(int value);

    [[nodiscard]] static int get_value();

};

class Array : public Value {
private:
    std::vector<Value *> values;
    size_t values_count{};

public:
    Array();

    explicit Array(const std::vector<Value *> &values);

    static int size();

    void append(Value *value);

    void remove(int index);

    const Value *operator[](int index) const;
};

class Object : public Value {
private:
    std::unordered_map<std::string, Value *> data;
    size_t data_count{};

public:
    Object();

    explicit Object(const std::unordered_map<std::string, Value *> &data);

    static int size();

    static std::vector<std::string> keys();

    void insert(const std::string &str, Value *value);

    void remove(const std::string &key);

    const Value *operator[](const std::string &key) const;

    virtual ~Object();
};

class Null : public Value {
};