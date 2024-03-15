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

Value *Array::operator[](int index) {
    return nullptr;
}

Object::Object(const std::vector<std::pair<std::string, Value *>> &pairs) {

}

std::vector<std::string> Object::keys() {
    return {};
}

void Object::insert(const std::string &str, Value *value) {

}

void Object::remove(const std::string &key) {

}

Value *Object::operator[](const std::string &key) {
    return nullptr;
}

int Object::size() {
    return 0;
}

Object::~Object() = default;
