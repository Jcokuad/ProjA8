// test_vector_iterator.cpp
//#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "array/vector.hpp"
#include "array/matrix.hpp"

using dsac::array::Matrix;

TEST_CASE("Matrix addition: same dimensions", "[tag]") {
    REQUIRE(true);
}

TEST_CASE("Matrix throws on negative dimensions") {
    REQUIRE_THROWS_AS(Matrix(-4, 5), std::out_of_range);
    REQUIRE_THROWS_AS(Matrix(5, -1), std::out_of_range);
    REQUIRE_THROWS_AS(Matrix(-2, -3), std::out_of_range);
}

TEST_CASE("Matrix initializes to zero") {
    Matrix first(3, 5);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            REQUIRE(first(i, j) == 0);
        }
    }
}

TEST_CASE("Matrix throws on invalid indices") {
    Matrix first(3, 5);

    REQUIRE_THROWS_AS(first(-2, 0), std::out_of_range);
    REQUIRE_THROWS_AS(first(3, 0), std::out_of_range);
    REQUIRE_THROWS_AS(first(4, 10), std::out_of_range);
    REQUIRE_THROWS_AS(first(0, 5), std::out_of_range);
}

TEST_CASE("Matrix operator() allows reading values and adding values") {
    Matrix first(2, 3);

    first(0, 0) = 2;
    first(0, 1) = 4;
    first(0, 2) = 6;
    first(1, 0) = 8;
    first(1, 1) = 10;
    first(1, 2) = 12;

    REQUIRE(first(0, 0) == 2);
    REQUIRE(first(0, 1) == 4);
    REQUIRE(first(0, 2) == 6);
    REQUIRE(first(1, 0) == 8);
    REQUIRE(first(1, 1) == 10);
    REQUIRE(first(1, 2) == 12);
}

TEST_CASE("Matrix addition throws when dimensions don't match") {
    Matrix x(2, 2);
    Matrix y(3, 3);

    REQUIRE_THROWS_AS(x + y, std::out_of_range);
}

TEST_CASE("Matrix addition works correctly") {
    Matrix x(2, 2);
    Matrix y(2, 2);

    x(0, 0) = 2;
    x(0, 1) = 4;
    x(1, 0) = 6;
    x(1, 1) = 8;

    y(0, 0) = 9;
    y(0, 1) = 7;
    y(1, 0) = 5;
    y(1, 1) = 3;

    Matrix z = x + y;

    REQUIRE(z(0, 0) == 11);
    REQUIRE(z(0, 1) == 11);
    REQUIRE(z(1, 0) == 11);
    REQUIRE(z(1, 1) == 11);
}

