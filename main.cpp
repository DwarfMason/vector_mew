#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "vector.h"

TEST_CASE("CONSTRUCTORS_TEST") {
  Vector<int> x1;
  Vector<double> x2(12);
  Vector<std::vector<int>> x3(10, 15);
  Vector<int> x4 = {1, 2, 3, 4, 5};
  Vector<int> x5(x4);
  REQUIRE(x1.empty());
  REQUIRE(x2.size() == 12);
  REQUIRE(x4[0] == 1);
  REQUIRE(x4[1] == 2);
  REQUIRE(x4[2] == 3);
  REQUIRE(x4[3] == 4);
  REQUIRE(x4[4] == 5);
  REQUIRE(x5[0] == 1);
  REQUIRE(x5[1] == 2);
  REQUIRE(x5[2] == 3);
  REQUIRE(x5[3] == 4);
  REQUIRE(x5[4] == 5);
}
