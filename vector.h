#pragma once

#include <cstdint>
#include <utility>
#include <stdexcept>

template<typename T>
class Vector {
    size_t size_ = 0;
    size_t capacity_ = 0;
    T *value_ = nullptr;

public:
    Vector() = default;

    explicit Vector(const size_t size) : size_(size), capacity_(size), value_(new T[size_]) {
    };

    ~Vector() {
        delete[] value_;
    };

    Vector &operator=(const Vector &other) {
        if (this != &other) {
            Resize(other.size_);
            for (size_t i = 0; i < other.size_; ++i) {
                value_[i] = other.value_[i];
            }
        }
        return *this;
    }

    Vector &operator=(Vector &&other) noexcept {
        if (this != &other) {
            delete[] value_;
            size_ = std::exchange(other.size_, 0);
            capacity_ = std::exchange(other.capacity_, 0);
            value_ = std::exchange(other.value_, nullptr);
        }
        return *this;
    }

    Vector(const Vector &other) : size_(other.size_), capacity_(other.capacity_) {
        if (other.size_ == 0) {
            value_ = nullptr;
            return;
        }
        value_ = new T[size_];
        for (size_t i = 0; i < size_; ++i) {
            value_[i] = other.value_[i];
        }
    }

    Vector(Vector &&other) noexcept : size_(std::exchange(other.size_, 0)),
                                      capacity_(std::exchange(other.capacity_, 0)),
                                      value_(std::exchange(other.value_, nullptr)) {
    };


    void Assign(const size_t size, const T &value) {
        delete[] value_;
        value_ = new T[size];
        size_ = size;
        capacity_ = size;
        for (size_t i = 0; i < size; ++i) {
            value_[i] = value;
        }
    }

    T &At(const size_t pos) {
        if (pos >= size_) {
            throw std::out_of_range("Position is out of range");
        }

        return value_[pos];
    }

    const T &At(const size_t pos) const {
        if (pos >= size_) {
            throw std::out_of_range("Position is out of range");
        }

        return value_[pos];
    }

    T &operator[](const size_t pos) {
        return value_[pos];
    }

    const T &operator[](const size_t pos) const {
        return value_[pos];
    }

    T &Front() {
        return value_[0];
    };

    const T &Front() const {
        return value_[0];
    };

    T &Back() {
        return value_[size_ - 1];
    };

    const T &Back() const {
        return value_[size_ - 1];
    };

    T *Data() {
        return value_;
    }

    const T *Data() const {
        return value_;
    }

    T *Begin() {
        return value_;
    };

    const T *Begin() const {
        return value_;
    };

    T *End() {
        return value_ + size_;
    };

    const T *End() const {
        return value_ + size_;
    };


    bool Empty() const {
        return size_ == 0;
    }

    size_t Size() const {
        return size_;
    }

    void Reserve(const size_t capacity) {
        if (capacity <= capacity_) {
            return;
        }

        T *new_vector = new T[capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_vector[i] = std::move(value_[i]);
        }

        delete[] value_;
        value_ = new_vector;
        capacity_ = capacity;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void Clear() {
        size_ = 0;
    }

    void Insert(const size_t pos, const T &value) {
        if (pos > size_) {
            throw std::out_of_range("Position is out of range");
        }

        if (size_ >= capacity_) {
            Reserve(capacity_ == 0 ? 1 : 2 * capacity_);
        }

        for (size_t i = size_; i > pos; --i) {
            value_[i] = std::move(value_[i - 1]);
        }

        value_[pos] = value;
        ++size_;
    }

    void Push_back(const T &value) {
        if (size_ >= capacity_) {
            Reserve(capacity_ == 0 ? 1 : 2 * capacity_);
        }

        value_[size_] = value;
        ++size_;
    }

    void Push_back(T &&value) {
        if (size_ >= capacity_) {
            Reserve(capacity_ == 0 ? 1 : 2 * capacity_);
        }

        value_[size_] = std::move(value);
        ++size_;
    }

    void Pop_back() {
        --size_;
    }


    void Resize(const size_t size, const T &value = T()) {
        if (size <= size_) {
            size_ = size;
            return;
        }

        if (size <= capacity_) {
            for (size_t i = size_; i < size; ++i) {
                value_[i] = value;
            }
            size_ = size;
            return;
        }

        T *new_vector = new T[size];
        for (size_t i = 0; i < size; ++i) {
            if (i < size_) {
                new_vector[i] = std::move(value_[i]);
            } else {
                new_vector[i] = value;
            }
        }

        delete[] value_;
        size_ = size;
        capacity_ = size;
        value_ = new_vector;
    }
};
