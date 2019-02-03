#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

template<typename T>
class Iterator {
public:
    typedef typename std::iterator_traits<Iterator<T>> traits;
    typedef typename traits::difference_type difference_type;
    typedef typename traits::value_type value_type;
    typedef typename traits::pointer pointer;
    typedef typename traits::reference reference;
    typedef typename traits::iterator_category iterator_category;

    explicit Iterator(pointer ptr = nullptr) : ptr_(ptr){}

    Iterator(const Iterator &other) : ptr_(other.ptr_){}

    Iterator &operator=(const Iterator &value){
        ptr_ = value.ptr_;
        return *this;
    }

    Iterator &operator++(){
        ++ptr_;
        return *this;
    }

    Iterator &operator--(){
        --ptr_;
        return *this;
    }

    const Iterator operator++(int){
        pointer ptr = ptr_;
        ptr_++;
        return Iterator(ptr);
    }

    const Iterator operator--(int){
        pointer ptr = ptr_;
        ptr_--;
        return Iterator(ptr);
    }

    Iterator &operator+=(difference_type value){
        ptr_ += value;
        return *this;
    }

    Iterator &operator-=(difference_type value){
        ptr_ -= value;
        return *this;
    }

    difference_type operator-(const Iterator &value) const{
        return ptr_ - value.ptr_;
    }

    Iterator operator+(difference_type value) const{
        return *this + value;
    }

    Iterator operator-(difference_type value) const{
        return std::forward(*this - value);
    }

    reference operator*() const{
        return *ptr_;
    }

    pointer operator->() const{
        return ptr_;
    }

    reference operator[](difference_type value) const{
        return *(*this + value);
    }

    bool operator==(const Iterator &value) const{
        return ptr_ == value.ptr_;
    }

    bool operator!=(const Iterator &value) const{
        return ptr_ != value.ptr_;
    }

    bool operator>(const Iterator &value) const{
        return ptr_ > value.ptr_;
    }

    bool operator<(const Iterator &value) const{
        return ptr_ < value.ptr_;
    }

    bool operator>=(const Iterator &value) const{
        return ptr_ >= value.ptr_;
    }

    bool operator<=(const Iterator &value) const {
        return ptr_ <= value.ptr_;
    }

private:
    pointer ptr_;
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
    typedef typename Iterator<T> iterator;
    typedef typename ConstIterator<T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


    // Сonstructors

    Vector();

    Vector(size_type a_size);

    Vector(size_type a_size, const_reference a_value,
           const allocator_type &alloc = allocator_type());

    Vector(std::initializer_list<value_type> il,
           const allocator_type &alloc = allocator_type());

    Vector(const Vector &other, const allocator_type &alloc);

    template<class InputIterator>
    Vector(InputIterator a_first, InputIterator a_last,
           const allocator_type &alloc = allocator_type());

    Vector &operator=(const Vector &other);

    ~Vector();

    // Iterators

    iterator begin();

    const_iterator begin() const;

    iterator end();

    const_iterator end() const;

    reverse_iterator rbegin();

    const_reverse_iterator rbegin() const;

    reverse_iterator rend();

    const_reverse_iterator rend() const;

    // Capacity

    size_type size() const;

    size_type capacity() const;

    bool empty() const;

    void reserve(size_type a_size);

    void resize(size_type a_size);

    // Element access

    reference front();

    const_reference front() const;

    reference back();

    const_reference back() const;

    reference at(size_type a_index);

    const_reference at(size_type a_index) const;

    reference operator[](size_type a_index);

    const_reference operator[](size_type a_index) const;

    // Modifiers

    iterator insert(iterator a_position, const T &a_value);

    template<class... Args>
    iterator emplace(iterator a_position, Args &&... args);

    template<class... Args>
    iterator emplace_back(Args &&... args);

    void push_back(const T &a_value);

    // [first, last}
    iterator erase(iterator a_first, iterator a_last);

    iterator erase(iterator a_position);

    void clear();

    void pop_back();
};
