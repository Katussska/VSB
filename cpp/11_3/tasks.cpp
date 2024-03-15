#include "tasks.h"

Integer::Integer(int value) {

}

int Integer::get_value() {
    return 0;
}

Array::Array(const std::vector<Value *> &values) {

}

int Array::size() {
    return 0;
}

void Array::append(Value *value) {
}

void Array::remove(int index) {


}

const Value *Array::operator[](int index) const {
    return nullptr;
}

Array::Array() = default;

Object::Object(const std::unordered_map<std::string, Value *> &data) {

}

std::vector<std::string> Object::keys() {
    return {};
}

void Object::insert(const std::string &str, Value *value) {

}

void Object::remove(const std::string &key) {

}

int Object::size() {
    return 0;
}

const Value *Object::operator[](const std::string &key) const {
    return nullptr;
}

Object::Object() = default;

Object::~Object() = default;

