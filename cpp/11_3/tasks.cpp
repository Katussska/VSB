#include "tasks.h"

Integer::Integer(int value) : number(value) {}

Integer *Integer::clone() const {
    //TODO:
    return nullptr;
}

void Integer::accept(class Visitor &visitor) {
    //TODO:
}

const Value &Integer::operator[](size_t index) const {
    throw std::runtime_error("Indexing not supported.");
}

const Value &Integer::operator[](const std::string &key) const {
    throw std::runtime_error("Indexing not supported.");
}

int Integer::get_value() {
    //TODO:
    return 0;
}

void Integer::accept(Visitor &visitor) const {
    //TODO:
}

Array::Array(const std::vector<Value *> &values) {
    //TODO:
}

void Array::append(Value *value) {
    //TODO:
}

Array *Array::clone() const {
    //TODO:
    return nullptr;
}

void Array::accept(class Visitor &visitor) {
    //TODO:
}

const Value &Array::operator[](const std::string &key) const {
    throw std::runtime_error("Indexing not supported.");
}

const Value &Array::operator[](size_t index) const {
    if (index < values.size())
        return *(values[index]);
    else
        throw std::runtime_error("Index out of Array's size.");
}

int Array::size() {
    //TODO:
    return 0;
}

[[maybe_unused]] void Array::remove(size_t index) {
    //TODO:
}

void Array::accept(Visitor &visitor) const {
    //TODO:
}

Array::~Array() = default;

Array::Array() = default;

Object::Object(const std::unordered_map<std::string, Value *> &data) {
    //TODO:
}

void Object::insert(const std::string &str, Value *value) {
    //TODO:
}

void Object::remove(const std::string &key) {
    //TODO:
}

Object *Object::clone() const {
    return nullptr;
}

void Object::accept(class Visitor &visitor) {
    //TODO:
}

const Value &Object::operator[](size_t index) const {
    throw std::runtime_error("Indexing not supported.");
}

const Value &Object::operator[](const std::string &key) const {
    auto temp = data.find(key);

    if (temp != data.end())
        return *(temp->second);
    else
        throw std::runtime_error("Key not found.");
}

int Object::size() {
    //TODO:
    return 0;
}

std::vector<std::string> Object::keys() {
    //TODO:
    return {};
}

void Object::accept(Visitor &visitor) const {
    //TODO:
}

Object::~Object() = default;

Object::Object() = default;

Null *Null::clone() const {
    //TODO:
    return nullptr;
}

void Null::accept(class Visitor &visitor) {
}

const Value &Null::operator[](size_t index) const {
    throw std::runtime_error("Indexing not supported.");
}

const Value &Null::operator[](const std::string &key) const {
    throw std::runtime_error("Indexing not supported.");
}

void Null::accept(Visitor &visitor) const {
    //TODO:
}

[[maybe_unused]] void RemoveNullVisitor::visit(Null &null) {
    //TODO:
}

[[maybe_unused]] void RemoveNullVisitor::visit(Array &array) {
    //TODO:
}

[[maybe_unused]] void RemoveNullVisitor::visit(Object &object) {
    //TODO:
}

void PrintVisitor::visit(const Integer &integer) {
    //TODO:
}

void PrintVisitor::visit(const Null &null) {
    //TODO:
}

void PrintVisitor::visit(const Array &array) {
    //TODO:
}

void PrintVisitor::visit(const Object &object) {
    //TODO:
}
