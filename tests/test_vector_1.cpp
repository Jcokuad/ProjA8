// test_vector.cpp
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "array/vector.hpp"


TEST_CASE("Default constructor creates empty vector", "[tag]") {
    dsac::array::Vector<int> v;
    bool ok = (v.size() == 0) && (v.capacity() == 0) && v.empty();

    REQUIRE(ok);
}