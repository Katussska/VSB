#include <algorithm>
#include <iostream>
#include <functional>
#include <cstring>
#include <string_view>
#include <regex>

struct S {

    size_t x = 0;

    S(const std::string_view sv);

};

S::S(const std::string_view sv) : x(sv.size()) {}

int fn(int) {
    return 13;
}

std::vector<int> map(
        const std::vector<int> &v,
        const auto &fn) {

    std::vector<int> dest;
    dest.reserve(v.size());

    for (const int i: v) {
        dest.emplace_back(fn(i));
    }

    return dest;
}

int main() {
    // S s { std::string { "string" } };
    S s{std::string{"string"}};
    std::cout << s.x << std::endl;

    std::regex re(R"([a-zA-Z]{2,4}\d{3})");
    std::cmatch m;

    if (std::regex_match("cd123", m, re)) {
        std::cout << "Found" << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }

    struct Callable {

        int y = 0;

        Callable(int y) : y(y) {}

        int operator()(int x) {
            return x + y;
        }
    };

    Callable callable{10};

    std::vector<int> v{1, 2, 3, 4, 5};

    auto c = [y = 5, v = std::move(v)](int x) -> int {
        for (int i: v) {
            std::cout << i << std::endl;
        }
        return x + y;
    };

    auto d = [](int x) -> int {
        return x;
    };

    std::function<int(int)> e = [](int) -> int { return 0; };

    std::cout << e(37) << std::endl;

    auto vec = map(
            std::vector<int>{4, 5, 6},
            e
    );

    for (int i: vec) {
        std::cout << i << std::endl;
    }

}
