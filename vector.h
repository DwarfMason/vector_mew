#pragma once

#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

namespace iterator {

template<typename T>
class Iterator : std::iterator<std::random_access_iterator_tag, T> {
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
    return *this + value;
  }

  Iterator operator-(difference_type value) const {
    return std::forward(*this - value);
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

}

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
  typedef typename iterator::Iterator<T> iterator;
 // typedef typename ConstIterator<T> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
 // typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


  // Сonstructors

  Vector() : size_(0), real_size_(0),
             alloc_(allocator_type()), data_(nullptr) {};

  Vector(size_type a_size) : real_size_(0),
                             alloc_(allocator_type()), data_(nullptr) { resize(a_size); };

  Vector(size_type a_size, const_reference a_value,
         const allocator_type &alloc = allocator_type()) :
      real_size_(0), alloc_(alloc), data_(nullptr) {
    resize(a_size);
    for (size_type i = 0; i < size_; i++)
      data_[i] = a_value;
  };

  Vector(std::initializer_list<value_type> il,
         const allocator_type &alloc = allocator_type())
      : alloc_(alloc), data_(nullptr), real_size_(0) {
    resize(il.size());
    std::copy(il.begin(), il.end(), begin());
  }

  Vector(const Vector &other, const allocator_type &alloc = allocator_type())
  : alloc_(alloc) {
    resize(other.size());
    std::copy(other.begin(), other.end(), begin());
  }

  template<class InputIterator>
  Vector(InputIterator a_first, InputIterator a_last,
         const allocator_type &alloc = allocator_type())
      : alloc_(alloc), real_size_(0), data_(nullptr) {
    resize(a_last - a_first);
    std::copy(a_first, a_last, begin());
  }

  Vector &operator=(const Vector &other) {
    resize(other.size());
    std::copy(other.begin(), other.end(), begin());
    return *this;
  }

  ~Vector() {
    for (size_type i = 0; i < real_size_; i++)
      data_[i].~T();
    alloc_.deallocate(data_, real_size_);
  }

  // Iterators

  iterator begin() {
    return iterator(data_);
  }

  //const_iterator begin() const;

  iterator end() {
    return iterator(data_ + size_);
  }

 // const_iterator end() const;

  reverse_iterator rbegin() {
    return reverse_iterator(end());
  }

 // const_reverse_iterator rbegin() const;

  reverse_iterator rend() {
    return reverse_iterator(begin());
  }

 // const_reverse_iterator rend() const;

  // Capacity

  size_type size() const {
    return size_;
  }

  size_type capacity() const {
    return real_size_;
  }

  bool empty() const {
    return size_ == 0;
  }

  void reserve(size_type a_size) {
    if (a_size > real_size_) {
      size_type reserve_size = a_size * 2;
      pointer new_data = alloc_.allocate(reserve_size);
      if (data_ != nullptr) {
        for (size_type i = 0; i < real_size_; i++)
          new_data[i] = std::move(data_[i]);
        alloc_.deallocate(data_, real_size_);
      }
      real_size_ = reserve_size;
      data_ = new_data;
    }
  }

  void resize(size_type a_size) {
    if (real_size_ < a_size)
      reserve(a_size);
    size_ = a_size;
  }

  // Element access

  reference front() {
    return data_[0];
  }

  //const_reference front() const;

  reference back() {
    return data_[size_ - 1];
  }

  //const_reference back() const;

  reference at(size_type a_index) {
      return data_[a_index];
  }

  //const_reference at(size_type a_index) const;

  reference operator[](size_type a_index) {
    return at(a_index);
  }

 // const_reference operator[](size_type a_index) const;

  // Modifiers

  iterator insert(iterator a_position, const T &a_value) {
    resize(size_ + 1);
    std::copy_backward(a_position, end() - 1, end());
    *a_position = std::move(a_value);
    return a_position;
  }

  template<class... Args>
  iterator emplace(iterator a_position, Args &&... args) {
    insert(a_position, T(args...));
  }

  template<class... Args>
  iterator emplace_back(Args &&... args) {
    resize(size_ + 1);
    back() = T({std::forward<Args>(args)...});
  }

  void push_back(const T &a_value) {
    resize(size_ + 1);
    back() = std::move(a_value);
  }

  // [first, last}
  iterator erase(iterator a_first, iterator a_last) {
    for (auto it = a_first; it < a_last; it++)
      it->~T();
    std::copy(a_last, end(), a_first);
    resize(size_ - a_last + a_first);
    return a_last;
  }

  iterator erase(iterator a_position) {
    a_position->~T();
    std::copy(a_position + 1, end(), a_position);
    resize(size_ - 1);
    return a_position;
  }

  void clear() {
    for (size_type i = 0; i < size_; i++)
      data_[i].~T();
    size_ = 0;
    real_size_ = 0;
  }

  void pop_back() {
    back().~T();
    resize(size_ - 1);
  }

 private:
  size_type size_;
  size_type real_size_;
  allocator_type alloc_;
  pointer data_;
};
