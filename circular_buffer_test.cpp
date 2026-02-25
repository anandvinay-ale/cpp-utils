#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

#include "circular_buffer.hpp"

static void test_empty_buffer() {
    circular_buffer<int, 4> cb;
    assert(cb.empty());
    assert(!cb.full());
    assert(cb.size() == 0);
    assert(cb.capacity() == 4);
}

static void test_push_and_front_back() {
    circular_buffer<int, 4> cb;
    cb.push_back(10);
    cb.push_back(20);
    cb.push_back(30);
    assert(cb.size() == 3);
    assert(cb.front() == 10);
    assert(cb.back() == 30);
}

static void test_pop_front() {
    circular_buffer<int, 4> cb;
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.pop_front();
    assert(cb.front() == 2);
    assert(cb.size() == 2);
}

static void test_full_buffer() {
    circular_buffer<int, 3> cb;
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    assert(cb.full());
}

static void test_wrap_around() {
    circular_buffer<int, 3> cb;
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);
    cb.pop_front();
    cb.push_back(4);
    assert(cb.front() == 2);
    assert(cb.back() == 4);
    assert(cb.size() == 3);
}

static void test_clear() {
    circular_buffer<int, 4> cb;
    cb.push_back(1);
    cb.push_back(2);
    cb.clear();
    assert(cb.empty());
    assert(cb.size() == 0);
}

static void test_overflow_throws() {
    circular_buffer<int, 2> cb;
    cb.push_back(1);
    cb.push_back(2);
    bool threw = false;
    try {
        cb.push_back(3);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);
}

static void test_underflow_throws() {
    circular_buffer<int, 2> cb;
    bool threw = false;
    try {
        cb.pop_front();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);
}

static void test_string_type() {
    circular_buffer<std::string, 3> cb;
    cb.push_back("hello");
    cb.push_back("world");
    assert(cb.front() == "hello");
    assert(cb.back() == "world");
    cb.pop_front();
    assert(cb.front() == "world");
}

int main() {
    test_empty_buffer();
    test_push_and_front_back();
    test_pop_front();
    test_full_buffer();
    test_wrap_around();
    test_clear();
    test_overflow_throws();
    test_underflow_throws();
    test_string_type();
    std::cout << "All tests passed.\n";
    return 0;
}
