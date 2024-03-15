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

    static int get_value();

};

class Array : public Value {
private:
    std::vector<Value *> values;
    size_t values_count{};

public:
    explicit Array(const std::vector<Value *> &values);

    static int size();

    void append(Value *value);

    void remove(int index);

    Value *operator[](int index);
};

class Object : public Value {
private:
    std::unordered_map<std::string, Value *> data;
    size_t data_count;

public:
    explicit Object(const std::vector<std::pair<std::string, Value *>> &pairs);

    static int size();

    static std::vector<std::string> keys();

    void insert(const std::string &str, Value *value);

    void remove(const std::string &key);

    Value *operator[](const std::string &key);

    virtual ~Object();
};

class Null : public Value {
};