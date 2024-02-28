#include <cstring>
#include <iostream>
#include <optional>
#include <vector>

int work(int x) {
    std::cout << "int work(int x)" << std::endl;
    return 0;
}

int work(int* x) {
    std::cout << "int work(int* x)" << std::endl;
    return 0;
}

struct Alignment {
    int i;
    int i2;
    char c;
    char c2;
};

class A {

};

class B : public A {

};

class MyString {
    mutable char* buffer = nullptr;
    size_t size = 0;
    size_t reserved = 0;

public:

    static int a;
    static MyString createString(const char* ptr);

    MyString() = default;
    explicit MyString(const char* ptr);
    MyString(const MyString& str);
    MyString(MyString&& str);

    MyString& operator=(const MyString& str);
    MyString& operator=(MyString&& str);

    ~MyString();

    char& operator[](const size_t idx);
    char operator[](const size_t idx) const;

    MyString& operator+=(const MyString& str);

    operator bool() const;

    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
};

MyString::operator bool() const {
    for (size_t i = 0; i < size; ++i) {
        if (not std::isspace(buffer[i])) {
            return true;
        }
    }
    return false;
}
 
int MyString::a = 0;

MyString MyString::createString(const char* ptr) {
    return MyString(ptr);
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    if (str.buffer == nullptr) {
        return os;
    }
    return os << str.buffer;
}

MyString::MyString(const char* ptr) {
    size = strlen(ptr);
    reserved = size + 1;
    buffer = new char[reserved];
    std::copy(ptr, ptr+reserved, buffer);
}

MyString::MyString(const MyString& str) {
    size = str.size;
    reserved = str.reserved;
    buffer = new char[reserved];
    std::copy(str.buffer, str.buffer+reserved, buffer);
}

MyString::MyString(MyString&& str) {
    size = str.size;
    reserved = str.reserved;
    buffer = str.buffer;
    str.buffer = nullptr;
}

MyString& MyString::operator=(const MyString& str) {

    if (buffer != nullptr) {
        delete[] buffer;
    }

    size = str.size;
    reserved = str.reserved;
    buffer = new char[reserved];
    std::copy(str.buffer, str.buffer+reserved, buffer);

    return *this;
}

MyString& MyString::operator=(MyString&& str) {

    if (buffer != nullptr) {
        delete[] buffer;
    }

    size = str.size;
    reserved = str.reserved;
    buffer = str.buffer;
    str.buffer = nullptr;

    return *this;
}

MyString::~MyString() {
    if (buffer != nullptr) {
        delete[] buffer;
    }
}

char& MyString::operator[](const size_t idx) {
    return buffer[idx];
}

char MyString::operator[](const size_t idx) const {
    return buffer[idx];
}

MyString& MyString::operator+=(const MyString& str) {
    const auto newSize = size + str.size;
    if (reserved < newSize+1) {
        reserved = newSize+1; 
        char* newData = new char[reserved];
        std::copy(buffer, buffer + size + 1, newData);
        delete[] buffer;
        buffer = newData;
    }
    std::copy(str.buffer, str.buffer + str.reserved, buffer + size);
    size = newSize;

    return *this;
}

enum class Color {
    Red = 1,
    Green,
    Blue
};

enum class Aircraft {
    A350 = 1,
    A380,
    A330
};

struct Bitfield {
    char a : 3;
    char b : 3;
};

union Union {
    std::string str;
    int i;
};

void doWork(const MyString& str) {
    std::cout << str << std::endl;
}

struct S {
    int x;
    int y;
    int z;
};

int main(int argc, const char** argv) {

    S s { 1, 2, 3 };

    std::vector<int> vec { 1, 2, 3, 4, 5, 6 };

    std::string str = "aaaa";
    std::cout << sizeof(std::string) << std::endl;
    work(0);
    work(nullptr);

    Color c = Color::Red;
    Aircraft a = Aircraft::A350;

    std::cout << sizeof(Bitfield) << std::endl;
    std::cout << sizeof(Union) << std::endl;

    doWork(MyString("string from char ptr"));

    std::optional<int> opt = 0;
    opt = std::nullopt;

    MyString str2 { "bbb" };
    MyString str3{};
    str2 += MyString { "ccc" };
    str2.operator+=(MyString { "ddd" });
    operator<<(std::cout, str2) << std::endl;
    // std::cout << str2 << std::endl;
    //
    if (MyString("    ")) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
}
