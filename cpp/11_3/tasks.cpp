#include <sstream>
#include <algorithm>
#include "tasks.h"

Integer::Integer(int value) : number(value) {}

Integer *Integer::clone() const {
    return new Integer(*this);
}

Value *Integer::operator[](size_t index) const {
    throw std::runtime_error("Indexing not supported.");
}

Value *Integer::operator[](const std::string &key) const {
    throw std::runtime_error("Indexing not supported.");
}

int Integer::get_value() const {
    return number;
}

void Integer::accept(const Visitor &visitor) {
    visitor.visit(*this);
}

Array::Array(const std::vector<Value *> &values) : values(values) {}

void Array::append(Value *value) {
    values.push_back(value);
}

Array *Array::clone() const {
    std::vector<Value *> cloned;

    for (const auto &value: values)
        cloned.push_back(value->clone());

    return new Array(cloned);
}

Value *Array::operator[](const std::string &key) const {
    throw std::runtime_error("Indexing not supported.");
}

Value *Array::operator[](size_t index) const {
    if (index < values.size())
        return values[index];
    else
        return nullptr;
}

size_t Array::size() const {
    if (values.empty())
        return 0;

    return values.size();
}

[[maybe_unused]] void Array::remove(int index) {
    values.erase(values.begin() + index);
}

void Array::accept(const Visitor &visitor) {
    visitor.visit(*this);
}

Object::Object(const std::unordered_map<std::string, Value *> &pair) : data(pair) {}

void Object::insert(const std::string &key, Value *value) {
    data.insert_or_assign(key, value);
}

[[maybe_unused]] void Object::remove(const std::string &key) {
    data.erase(key);
}

Object *Object::clone() const {
    std::unordered_map<std::string, Value *> cloned;

    for (auto &pair: data)
        cloned[pair.first] = pair.second->clone();

    return new Object(cloned);
}

Value *Object::operator[](size_t index) const {
    throw std::runtime_error("Indexing not supported.");
}

Value *Object::operator[](const std::string &key) const {
    auto temp = data.find(key);

    if (temp != data.end())
        return temp->second;
    else
        return nullptr;
}

size_t Object::size() const {
    if (data.empty())
        return 0;

    return data.size();
}

std::vector<std::string> Object::keys() const {
    if (data.empty())
        return {};

    std::vector<std::string> keys;

    for (auto &pair: data) {
        keys.push_back(pair.first);
    }

    std::sort(keys.begin(), keys.end());

    return keys;
}

void Object::accept(const Visitor &visitor) {
    visitor.visit(*this);
}

Null *Null::clone() const {
    return new Null(*this);
}

Value *Null::operator[](size_t index) const {
    throw std::runtime_error("Indexing not supported.");
}

Value *Null::operator[](const std::string &key) const {
    throw std::runtime_error("Indexing not supported.");
}

void Null::accept(const Visitor &visitor) {
    visitor.visit(*this);
}

void RemoveNullVisitor::visit(Array &array) const {
    auto temp = array.values.begin();
    while (temp != array.values.end()) {
        if (dynamic_cast<Null *>(*temp) != nullptr) {
            delete *temp;
            temp = array.values.erase(temp);
        } else {
            ++temp;
        }
    }
}

void RemoveNullVisitor::visit(Object &object) const {
    auto temp = object.data.begin();
    while (temp != object.data.end()) {
        if (dynamic_cast<Null *>(temp->second) != nullptr) {
            delete temp->second;
            temp = object.data.erase(temp);
        } else {
            ++temp;
        }
    }
}


PrintVisitor::PrintVisitor(std::stringstream &stream) : stream(stream) {}

void PrintVisitor::visit(Integer &integer) const {
    stream << integer.get_value();
}

void PrintVisitor::visit(Null &null) const {
    stream << "Null";
}

void PrintVisitor::visit(Array &array) const {
    stream << "[";

    for (size_t i = 0; i < array.size(); ++i) {
        if (array.size() == 0)
            break;

        if (i > 0)
            stream << ", ";

        array[i]->accept(*this);
    }

    stream << "]";
}

void PrintVisitor::visit(Object &object) const {
    stream << "{";

    auto keys = object.keys();

    for (size_t i = 0; i < keys.size(); ++i) {
        if (keys.empty())
            break;

        if (i > 0)
            stream << ", ";

        stream << keys[i] << ": ";
        Value *value = object[keys[i]];
        if (value != nullptr) {
            value->accept(*this);
        } else {
            stream << "null";
        }
    }

    stream << "}";
}