#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>

template <typename T, std::size_t Capacity>
class circular_buffer {
public:
    static_assert(Capacity > 0, "Capacity must be greater than zero");

    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;

    circular_buffer() = default;

    bool empty() const noexcept { return size_ == 0; }
    bool full() const noexcept { return size_ == Capacity; }
    size_type size() const noexcept { return size_; }
    size_type capacity() const noexcept { return Capacity; }

    reference front() {
        if (empty()) throw std::out_of_range("circular_buffer is empty");
        return buf_[head_];
    }

    const_reference front() const {
        if (empty()) throw std::out_of_range("circular_buffer is empty");
        return buf_[head_];
    }

    reference back() {
        if (empty()) throw std::out_of_range("circular_buffer is empty");
        return buf_[(head_ + size_ - 1) % Capacity];
    }

    const_reference back() const {
        if (empty()) throw std::out_of_range("circular_buffer is empty");
        return buf_[(head_ + size_ - 1) % Capacity];
    }

    void push_back(const T& value) {
        if (full()) throw std::out_of_range("circular_buffer is full");
        buf_[(head_ + size_) % Capacity] = value;
        ++size_;
    }

    void push_back(T&& value) {
        if (full()) throw std::out_of_range("circular_buffer is full");
        buf_[(head_ + size_) % Capacity] = std::move(value);
        ++size_;
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("circular_buffer is empty");
        head_ = (head_ + 1) % Capacity;
        --size_;
    }

    void clear() noexcept {
        head_ = 0;
        size_ = 0;
    }

private:
    // Note: buf_ is fully value-initialized for all Capacity elements when the circular_buffer
    // is constructed. For non-trivial T and large Capacity, this may have performance and
    // memory implications, as all elements are constructed eagerly even when the buffer is empty.
    std::array<T, Capacity> buf_{};
    size_type head_{0};
    size_type size_{0};
};
