#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

template<typename T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
public:
    typedef typename std::iterator_traits<Iterator<T>> traits;
    typedef typename traits::difference_type difference_type;
    typedef typename traits::value_type value_type;
    typedef typename traits::pointer pointer;
    typedef typename traits::reference reference;
    typedef typename traits::iterator_category iterator_category;

    explicit Iterator(pointer ptr = nullptr) : ptr_(ptr) {}

    Iterator(const Iterator &other) : ptr_(other.ptr_) {}

    Iterator &operator=(const Iterator &value) {
        ptr_ = value.ptr_;
        return *this;
    }

    Iterator &operator++() {
        ++ptr_;
        return *this;
    }

    Iterator &operator--() {
        --ptr_;
        return *this;
    }

    const Iterator operator++(int) {
        pointer ptr = ptr_;
        ptr_++;
        return Iterator(ptr);
    }

    const Iterator operator--(int) {
        pointer ptr = ptr_;
        ptr_--;
        return Iterator(ptr);
    }

    Iterator &operator+=(difference_type value) {
        ptr_ += value;
        return *this;
    }

    Iterator &operator-=(difference_type value) {
        ptr_ -= value;
        return *this;
    }

    difference_type operator-(const Iterator &value) const {
        return ptr_ - value.ptr_;
    }

    Iterator operator+(difference_type value) const {
        Iterator tmp = *this;
        return tmp += value;
    }

    Iterator operator-(difference_type value) const {
        Iterator tmp = *this;
        return tmp -= value;
    }

    reference operator*() const {
        return *ptr_;
    }

    pointer operator->() const {
        return ptr_;
    }

    reference operator[](difference_type value) const {
        return *(*this + value);
    }

    bool operator==(const Iterator &value) const {
        return ptr_ == value.ptr_;
    }

    bool operator!=(const Iterator &value) const {
        return ptr_ != value.ptr_;
    }

    bool operator>(const Iterator &value) const {
        return ptr_ > value.ptr_;
    }

    bool operator<(const Iterator &value) const {
        return ptr_ < value.ptr_;
    }

    bool operator>=(const Iterator &value) const {
        return ptr_ >= value.ptr_;
    }

    bool operator<=(const Iterator &value) const {
        return ptr_ <= value.ptr_;
    }

private:
    pointer ptr_;
};

template<typename T>
class ConstIterator : public std::iterator<std::random_access_iterator_tag, T> {
public:
    typedef typename std::iterator_traits<Iterator<T>> traits;
    typedef typename traits::difference_type difference_type;
    typedef typename traits::value_type value_type;
    typedef typename traits::pointer pointer;
    typedef typename traits::reference reference;
    typedef typename traits::iterator_category iterator_category;

    explicit ConstIterator(pointer ptr = nullptr) : ptr_(ptr) {}

    ConstIterator(const ConstIterator &other) : ptr_(other.ptr_) {}

    ConstIterator &operator=(const ConstIterator &value) {
        ptr_ = value.ptr_;
        return *this;
    }

    ConstIterator &operator++() {
        ++ptr_;
        return *this;
    }

    ConstIterator &operator--() {
        --ptr_;
        return *this;
    }

    const ConstIterator operator++(int) {
        pointer ptr = ptr_;
        ptr_++;
        return ConstIterator(ptr);
    }

    const ConstIterator operator--(int) {
        pointer ptr = ptr_;
        ptr_--;
        return ConstIterator(ptr);
    }

    ConstIterator &operator+=(difference_type value) {
        ptr_ += value;
        return *this;
    }

    ConstIterator &operator-=(difference_type value) {
        ptr_ -= value;
        return *this;
    }

    difference_type operator-(const ConstIterator &value) const {
        return ptr_ - value.ptr_;
    }

    ConstIterator operator+(difference_type value) const {
        ConstIterator tmp = *this;
        return tmp += value;
    }

    ConstIterator operator-(difference_type value) const {
        ConstIterator tmp = *this;
        return tmp -= value;
    }

    reference operator*() const {
        return *ptr_;
    }

    pointer operator->() const {
        return ptr_;
    }

    reference operator[](difference_type value) const {
        return *(*this + value);
    }

    bool operator==(const ConstIterator &value) const {
        return ptr_ == value.ptr_;
    }

    bool operator!=(const ConstIterator &value) const {
        return ptr_ != value.ptr_;
    }

    bool operator>(const ConstIterator &value) const {
        return ptr_ > value.ptr_;
    }

    bool operator<(const ConstIterator &value) const {
        return ptr_ < value.ptr_;
    }

    bool operator>=(const ConstIterator &value) const {
        return ptr_ >= value.ptr_;
    }

    bool operator<=(const ConstIterator &value) const {
        return ptr_ <= value.ptr_;
    }

private:
    T *ptr_;
};

template<class T, class A = std::allocator<T>>
class Vector {
public:
    typedef A allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::size_type size_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer pointer;
    typedef typename A::const_pointer const_pointer;
    typedef class Iterator<T> iterator;
    typedef class ConstIterator<T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


    // Сonstructors

    Vector() : size_(0), capacity_(0),
               alloc_(allocator_type()), data_(nullptr) {};

    explicit Vector(size_type a_size) : capacity_(0),
                                        alloc_(allocator_type()), data_(nullptr) { resize(a_size); };

    Vector(size_type a_size, const_reference a_value,
           const allocator_type &alloc = allocator_type()) :
            capacity_(0), alloc_(alloc), data_(nullptr) {
        resize(a_size);
        for (size_type i = 0; i < size_; i++)
            data_[i] = a_value;
    };

    Vector(std::initializer_list<value_type> il,
           const allocator_type &alloc = allocator_type())
            : alloc_(alloc), data_(nullptr), capacity_(0) {
        resize(il.size());
        std::copy(il.begin(), il.end(), begin());
    }

    Vector(const Vector &other, const allocator_type &alloc = allocator_type())
            : capacity_(0), alloc_(alloc), data_(nullptr) {
        resize(other.size());
        std::copy(other.begin(), other.end(), begin());
    }

    template<class InputIterator>
    Vector(InputIterator a_first, InputIterator a_last,
           const allocator_type &alloc = allocator_type())
            : alloc_(alloc), capacity_(0), data_(nullptr) {
        resize(a_last - a_first);
        std::copy(a_first, a_last, begin());
    }

    Vector &operator=(const Vector &other) {
        resize(other.size());
        std::copy(other.begin(), other.end(), begin());
        return *this;
    }

    ~Vector() {
        for (size_type i = 0; i < capacity_; i++)
            data_[i].~T();
        alloc_.deallocate(data_, capacity_);
    }

    // Iterators

    iterator begin() {
        return iterator(data_);
    }

    const_iterator begin() const {
        return const_iterator(data_);
    }

    iterator end() {
        return iterator(data_ + size_);
    }

    const_iterator end() const {
        return const_iterator(data_ + size_);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    // Capacity

    size_type size() const {
        return size_;
    }

    size_type capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void reserve(size_type a_size) {
        if (a_size > capacity_) {
            size_type reserve_size = a_size * 2;
            pointer new_data = alloc_.allocate(reserve_size);
            if (data_ != nullptr) {
                for (size_type i = 0; i < capacity_; i++)
                    new_data[i] = std::move(data_[i]);
//                for (size_type i = 0; i < capacity_; i++)
//                    std::swap(data[i]. new_data[i]);
                   // std::copy(iterator(&data_[0]), iterator(&data_[capacity_ - 1]), new_data);
                alloc_.deallocate(data_, capacity_);
            }
            capacity_ = reserve_size;
            data_ = new_data;
        }
    }

    void resize(size_type a_size) {
        if (capacity_ < a_size)
            reserve(a_size);
        size_ = a_size;
    }

    void resize(size_type a_size, value_type value) {
        if (capacity_ < a_size)
            reserve(a_size);
        size_type prev_size = size_;
        size_ = a_size;
        for (size_type i = prev_size; i < size(); i++)
            data_[i] = value;
    }

    void assign(size_type a_size, value_type value) {
        if (capacity_ < a_size)
            reserve(a_size);
        size_ = a_size;
        for (size_type i = 0; i < size(); i++)
            data_[i] = value;
    }

    // Element access

    reference front() {
        return data_[0];
    }

    const_reference front() const {
        return data_[0];
    }

    reference back() {
        return data_[size_ - 1];
    }

    const_reference back() const {
        return data_[size_ - 1];
    }

    reference at(size_type a_index) {
        try {
            if (a_index >= size() || a_index < 0)
                throw 1;
            return data_[a_index];
        }
        catch (int thr) {
            std::cout << "index " << a_index << " is out of range! Initialized with 'end()' \n";
            return data_[size_];
        }
    }

    const_reference at(size_type a_index) const {
        try {
            if (a_index >= size() || a_index < 0)
                throw 1;
            return data_[a_index];
        }
        catch (int thr) {
            std::cout << "index " << a_index << " is out of range! Initialized with 'end()' \n";
            return data_[size_];
        }
    }

    reference operator[](size_type a_index) {
        return data_[a_index];
    }

    const_reference operator[](size_type a_index) const {
        return data_[a_index];
    }

    // Modifiers

    iterator insert(iterator a_position, const T &a_value) {
        resize(size_ + 1);
        std::copy_backward(a_position, end() - 1, end());
        *a_position = a_value;
        return a_position;
    }

    template<class... Args>
    iterator emplace(iterator a_position, Args &&... args) {
        resize(size_ + 1);
        std::move_backward(a_position, end() - 1, end());
        *a_position = T({std::forward<Args>(args)...});
        return a_position;
    }

    template<class... Args>
    iterator emplace_back(Args &&... args) {
        resize(size_ + 1);
        back() = T({std::forward<Args>(args)...});
        return (end() - 1);
    }

    void push_back(const T &a_value) {
        resize(size_ + 1);
        back() = a_value;
    }

    // [first, last}
    iterator erase(iterator a_first, iterator a_last) {
        for (auto it = a_first; it < a_last; it++)
            it->~T();
        std::move(a_last, end(), a_first);
        resize(size_ - (a_last - a_first));
        return a_last;
    }

    iterator erase(iterator a_position) {
        a_position->~T();
        std::move(a_position + 1, end(), a_position);
        resize(size_ - 1);
        return a_position;
    }

    void clear() {
        for (size_type i = 0; i < size_; i++)
            data_[i].~T();
        size_ = 0;
        capacity_ = 0;
    }

    void pop_back() {
        back().~T();
        resize(size_ - 1);
    }

private:
    size_type size_;
    size_type capacity_;
    allocator_type alloc_;
    pointer data_;
};
