#include <functional>
#include <iostream>

auto make_counter() {
    int count = 0;                               // data lives here
    return [count]() mutable -> int {            // capture by value
        return ++count;
    };
}

int main() {
    auto c1 = make_counter();
    auto c2 = make_counter();
    std::cout << c1() << " " << c1() << '\n';    // 1 2
    std::cout << c2() << '\n';                   // 1
}
