#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <iostream>
#include "vector.h"
#include <vector>

TEST_CASE("ITERATORS_CONSTRUCTORS_TEST") {
    auto *a = (int *) calloc(2, sizeof(int));
    Iterator<int> x1(a);
    REQUIRE(*x1 == *a);

    Iterator<int> x2(x1);
    REQUIRE(*x2 == *a);

    ConstIterator<int> x3(a);
    REQUIRE(*x3 == *a);

    ConstIterator<int> x4(x3);
    REQUIRE(*x4 == *a);
}

TEST_CASE("ITERATOR_ARITHMETIC") {
    // =
    int *a = (int *) calloc(5, sizeof(int));
    Iterator<int> x1(a);
    Iterator<int> x2 = x1;
    REQUIRE(x2 == x1);

    ConstIterator<int> x3(a);
    ConstIterator<int> x4 = x3;
    REQUIRE(x4 == x3);

    //++
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Iterator<int> x5(&vec[0]);
    REQUIRE(*++x5 == vec[1]);

    ConstIterator<int> x6(&vec[0]);
    REQUIRE(*++x6 == vec[1]);

    //--
    Iterator<int> x7(&vec[1]);
    REQUIRE(*--x7 == vec[0]);

    ConstIterator<int> x8(&vec[1]);
    REQUIRE(*--x8 == vec[0]);

    //++(int)
    Iterator<int> x9(&vec[0]);
    REQUIRE(*x9++ == vec[0]);
    REQUIRE(*x9 == vec[1]);

    ConstIterator<int> x10(&vec[0]);
    REQUIRE(*x10++ == vec[0]);
    REQUIRE(*x10 == vec[1]);

    //--(int)
    Iterator<int> x11(&vec[1]);
    REQUIRE(*x11-- == vec[1]);
    REQUIRE(*x11 == vec[0]);

    ConstIterator<int> x12(&vec[1]);
    REQUIRE(*x12-- == vec[1]);
    REQUIRE(*x12 == vec[0]);

    //+=
    Iterator<int> x13(&vec[0]);
    x13 += 2;
    REQUIRE(*x13 == vec[2]);

    ConstIterator<int> x14(&vec[0]);
    x14 += 2;
    REQUIRE(*x14 == vec[2]);

    //-=
    Iterator<int> x15(&vec[3]);
    x15 -= 1;
    REQUIRE(*x15 == vec[2]);

    ConstIterator<int> x16(&vec[3]);
    x16 -= 1;
    REQUIRE(*x16 == vec[2]);

    //-(iter)
    Iterator<int> x17(&vec[3]);
    REQUIRE(x17 - x15 == 1);

    ConstIterator<int> x18(&vec[3]);
    REQUIRE(x18 - x16 == 1);

    //+(iter)
    Iterator<int> x19(&vec[0]);
    REQUIRE(*(x19 + 2) == vec[2]);

    ConstIterator<int> x20(&vec[1]);
    REQUIRE(*(x20 + 2) == vec[3]);

    //-
    Iterator<int> x21(&vec[3]);
    REQUIRE(*(x21 - 1) == vec[2]);

    ConstIterator<int> x22(&vec[3]);
    REQUIRE(*(x22 - 1) == vec[2]);
}

TEST_CASE("*_[]_->") {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Iterator<int> x1(&vec[0]);

    REQUIRE(*x1 == vec[0]);
    REQUIRE(x1[2] == *(x1 + 2));

    std::vector<std::pair<int, int>> vec2 = {std::make_pair(1, 2), std::make_pair(3, 4)};
    Iterator<std::pair<int, int>> x2(&vec2[0]);
    REQUIRE(x2->first == vec2[0].first);
}

TEST_CASE("EQUALITY_TESTS") {
    //==
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Iterator<int> x1(&vec[0]);
    Iterator<int> x2(&vec[0]);
    ConstIterator<int> x3(&vec[0]);
    ConstIterator<int> x4(&vec[0]);

    REQUIRE((x1 == x2) == (*x1 == *x2));
    x2++;
    REQUIRE((x1 == x2) == (*x1 == *x2));

    REQUIRE((x3 == x4) == (*x3 == *x4));
    x3++;
    REQUIRE((x3 == x4) == (*x3 == *x4));

    //!=
    x1 = Iterator<int>(&vec[0]);
    x2 = Iterator<int>(&vec[0]);
    x3 = ConstIterator<int>(&vec[0]);
    x4 = ConstIterator<int>(&vec[0]);
    REQUIRE((x1 != x2) == (*x1 != *x2));
    x2++;
    REQUIRE((x1 != x2) == (*x1 != *x2));

    REQUIRE((x3 != x4) == (*x3 != *x4));
    x3++;
    REQUIRE((x3 != x4) == (*x3 != *x4));

    //>
    x1 = Iterator<int>(&vec[0]);
    x2 = Iterator<int>(&vec[0]);
    x3 = ConstIterator<int>(&vec[0]);
    x4 = ConstIterator<int>(&vec[0]);
    REQUIRE((x1 > x2) == (*x1 > *x2));
    x1++;
    REQUIRE((x1 > x2) == (*x1 > *x2));

    REQUIRE((x3 > x4) == (*x3 > *x4));
    x4++;
    REQUIRE((x3 > x4) == (*x3 > *x4));

    //<
    x1 = Iterator<int>(&vec[0]);
    x2 = Iterator<int>(&vec[0]);
    x3 = ConstIterator<int>(&vec[0]);
    x4 = ConstIterator<int>(&vec[0]);
    REQUIRE((x1 < x2) == (*x1 < *x2));
    x2++;
    REQUIRE((x1 < x2) == (*x1 < *x2));

    REQUIRE((x3 < x4) == (*x3 < *x4));
    x4++;
    REQUIRE((x3 < x4) == (*x3 < *x4));

    //>=
    x1 = Iterator<int>(&vec[0]);
    x2 = Iterator<int>(&vec[0]);
    x3 = ConstIterator<int>(&vec[0]);
    x4 = ConstIterator<int>(&vec[0]);
    REQUIRE((x1 >= x2) == (*x1 >= *x2));
    x2++;
    REQUIRE((x1 >= x2) == (*x1 >= *x2));

    REQUIRE((x3 >= x4) == (*x3 >= *x4));
    x4++;
    REQUIRE((x3 >= x4) == (*x3 >= *x4));

    //<=
    x1 = Iterator<int>(&vec[0]);
    x2 = Iterator<int>(&vec[0]);
    x3 = ConstIterator<int>(&vec[0]);
    x4 = ConstIterator<int>(&vec[0]);
    REQUIRE((x1 <= x2) == (*x1 <= *x2));
    x1++;
    REQUIRE((x1 <= x2) == (*x1 <= *x2));

    REQUIRE((x3 <= x4) == (*x3 <= *x4));
    x3++;
    REQUIRE((x3 <= x4) == (*x3 <= *x4));
}

TEST_CASE("VECTOR_CONSTRUCTORS_TEST") {
    Vector<float>::size_type size = 10;
    float value = 15;
    Vector<int> x1;
    Vector<double> x2(12);
    Vector<float> x3(size, value);
    Vector<int> x4 = {1, 2, 3, 4, 5};
    Vector<int> x5(x4);
    Vector<int> x6(x3.begin(), x3.end());
    REQUIRE(x1.empty());
    REQUIRE(x2.size() == 12);

    for (auto i : x3) {
        REQUIRE(i == 15);
    }

    for (int i = 0; i < x4.size(); i++) {
        REQUIRE(x4[i] == i + 1);
    }

    for (int i = 0; i < x4.size(); i++) {
        REQUIRE(x5[i] == i + 1);
    }

    for (auto i : x6) {
        REQUIRE(i == 15);
    }

    x1 = x4;
    for (int i = 0; i < x1.size(); i++) {
        REQUIRE(x1[i] == i + 1);
    }
}

TEST_CASE("VECTOR_ITERATORS") {
    // begin & end
    Vector<int> vec = {1, 2, 3, 4, 5};

    REQUIRE(vec.begin() == Iterator<int>(&vec[0]));
    REQUIRE(vec.end() == Iterator<int>(&vec[vec.size()]));

    const Vector<int> &ref_vec = vec;
    auto x1 = ref_vec.begin();
    REQUIRE(x1 == ConstIterator<int>(&vec[0]));
    x1 = ref_vec.end();
    REQUIRE(x1 == ConstIterator<int>(&vec[vec.size()]));

    // rbegin & rend
    REQUIRE(*vec.rbegin() == vec[vec.size() - 1]);
    REQUIRE(*vec.rend() == vec[-1]);

    REQUIRE(*ref_vec.rbegin() == vec[vec.size() - 1]);
    REQUIRE(*ref_vec.rend() == vec[-1]);
}

TEST_CASE("VECTOR_CAPACITY") {
    // Resize and reserve are used by copy constructor. There is no need to check.
    Vector<int> vec(10);
    REQUIRE(vec.size() == 10);
    REQUIRE(vec.capacity() == 20);

    vec = Vector<int>(12);
    REQUIRE(vec.size() == 12);
    REQUIRE(vec.capacity() == 20);

    vec = Vector<int>(0);
    REQUIRE(vec.empty());
    REQUIRE(vec.capacity() == 20);

    vec = Vector<int>(1);
    vec[0] = 10;

    vec.resize(40, 12);
    REQUIRE(vec.size() == 40);
    REQUIRE(vec.capacity() == 80);
    REQUIRE(vec[0] == 10);
    for (int i = 1; i < vec.size(); i++)
        REQUIRE(vec[i] == 12);

    vec.assign(120, 60);
    REQUIRE(vec.size() == 80);
    REQUIRE(vec.capacity() == 240);
    for (auto i : vec)
        REQUIRE(i == 60);
}

TEST_CASE("ELEMENT_ACCESS") {
    Vector<int> vec = {2, 3, 5, 7, 11, 13};
    const Vector<int> &ref_vec = vec;

    //front & back
    REQUIRE(vec.front() == 2);
    REQUIRE(ref_vec.front() == 2);

    REQUIRE(vec.back() == 13);
    REQUIRE(ref_vec.back() == 13);

    *vec.begin() = 8;
    *(vec.end() - 1) = 11;

    REQUIRE(vec.front() == 8);
    REQUIRE(ref_vec.front() == 8);

    REQUIRE(vec.back() == 11);
    REQUIRE(ref_vec.back() == 11);

    //at
    REQUIRE(vec.at(3) == 7);
    REQUIRE(ref_vec.at(5) == 11);

    REQUIRE(vec.at(40) == *vec.end());
    REQUIRE(ref_vec.at(30) == *ref_vec.end());

    //[]
    REQUIRE(vec[3] == 7);
    REQUIRE(ref_vec[5] == 11);

    vec[3] = 6;
    vec[5] = 100;

    REQUIRE(vec[3] == 6);
    REQUIRE(ref_vec[5] == 100);
}

TEST_CASE("MODIFIERS") {
    Vector<int> vec = {1, 3, 4, 5, 6};

    //insert
    int value = 2;
    vec.insert(Iterator<int>(&vec[1]), value);
    for (int i = 0; i < vec.size(); i++)
        REQUIRE(vec[i] == i + 1);

    //emplace & emplace_back
    Vector<std::pair<int, int>> vec2 = {std::make_pair(1, 2), std::make_pair(5, 6)};
    vec2.emplace<int, int>(Iterator<std::pair<int, int>>(&vec2[1]), 3, 4);

    REQUIRE(vec2.size() == 3);
    REQUIRE(vec2[1] == std::pair(3, 4));
    REQUIRE(vec2.front() == std::pair(1, 2));
    REQUIRE(vec2.back() == std::pair(5, 6));

    vec2.emplace_back<int, int>(10, 100);

    REQUIRE(vec2.size() == 4);
    REQUIRE(vec2[1] == std::pair(3, 4));
    REQUIRE(vec2.front() == std::pair(1, 2));
    REQUIRE(vec2.back() == std::pair(10, 100));

    vec2.push_back(std::pair<int, int>(42, 15));

    REQUIRE(vec2.size() == 5);
    REQUIRE(vec2[1] == std::pair(3, 4));
    REQUIRE(vec2.front() == std::pair(1, 2));
    REQUIRE(vec2.back() == std::pair(42, 15));
}

TEST_CASE("VECTOR_CLEANINGS") {
    Vector<int> vec = {1, 6, 12, 25};

    vec.erase(Iterator<int>(&vec[1]), Iterator<int>(&vec[4]));

    REQUIRE(vec.size() == 1);
    REQUIRE(vec[0] == 1);

    vec.erase(Iterator<int>(&vec[0]));
    REQUIRE(vec.empty());

    vec = {1, 6, 12, 25};
    vec.clear();
    REQUIRE(vec.empty());

    vec = {1, 6, 12, 25};
    vec.pop_back();
    REQUIRE(vec.size() == 3);
    REQUIRE(vec.back() == 12);
}

TEST_CASE("NO_COPY_CONSTRUCTOR") {
    class A {
    public:
        A(const A &value) = delete;

        explicit A(int value) : value_(value) {}

        int value_;
    };

    Vector<A> vec = {A(12), A(15)};
    REQUIRE(vec.front().value_ == A(12).value_);
    vec.emplace_back(100);
    REQUIRE(vec.back().value_ == A(100).value_);
    vec[1] = A(30);
    REQUIRE(vec[1].value_ == A(30).value_);
    vec.insert(Iterator<A>(&vec[0]), A(16));
    REQUIRE(vec.front().value_ == A(16).value_);
    vec.resize(1000, A(30));
    vec.erase(Iterator<A>(&vec[0]));
    REQUIRE(vec.size() == 999);
}

TEST_CASE("NO_DEFAULT_CONSTRUCTOR") {
    class A {
    public:
        A() = delete;

        explicit A(int value) : value_(value) {}

        int value_;
    };

    Vector<A> vec = {A(12), A(15)};
    REQUIRE(vec.front().value_ == A(12).value_);
    vec.emplace_back(100);
    REQUIRE(vec.back().value_ == A(100).value_);
    vec[1] = A(30);
    REQUIRE(vec[1].value_ == A(30).value_);
    vec.insert(Iterator<A>(&vec[0]), A(16));
    REQUIRE(vec.front().value_ == A(16).value_);
    vec.resize(1000, A(30));
    vec.erase(Iterator<A>(&vec[0]));
    REQUIRE(vec.size() == 999);
}
