#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "vector.h"
#include <vector>

TEST_CASE("ITERATORS_CONSTRUCTORS_TEST") {
  int *a = (int *) calloc(2, sizeof(int));
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

TEST_CASE("*_[]_->"){
  std::vector<int> vec = {1, 2, 3, 4, 5};
  Iterator<int> x1(&vec[0]);

  REQUIRE(*x1 == vec[0]);
  REQUIRE(x1[2] == *(x1 + 2));
}

TEST_CASE("EQUALITY_TESTS"){

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

