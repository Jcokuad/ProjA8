// test_vector_iterator.cpp
//#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "array/vector.hpp"
#include "array/matrix.hpp"

using dsac::array::Vector; // using statement allows me to use Vector instead of writing the full namespace from the header file

TEST_CASE("Vector test case", "[tag]") {
    REQUIRE(true);
}

TEST_CASE("Begin iterator references first element") {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    auto it = v.begin();
    REQUIRE(*it == 10);
}

TEST_CASE("Prefix and Postfix iterators work correctly") {
    Vector<int> v;
    v.push_back(5);
    v.push_back(10);
    v.push_back(15);

    auto it = v.begin();
    REQUIRE(*it == 5);
    
    auto old = it++;  // Assign current val then increment
    REQUIRE(*old == 5);
    REQUIRE(*it == 10);

    ++it;   // increment then assign
    REQUIRE(*it == 15); 

    auto old2 = it--;
    REQUIRE(*old2 == 15);
    REQUIRE(*it == 10);
}

TEST_CASE("Equality and inequality iterators work correctly") {
    Vector<int> v;
    v.push_back(5);
    v.push_back(10);
    v.push_back(15);

    auto it1 = v.begin();
    auto it2 = v.begin();
    auto it3 = v.end();

    REQUIRE(it1 == it2); // Checks Equality
    REQUIRE(it1 != it3); // Checks Inequality
}

TEST_CASE("Insert iterator inserts element before current iterator position") {
    Vector<int> v;
    v.push_back(5);
    v.push_back(15);
    v.push_back(20);
    v.push_back(25);

    auto it = v.begin();
    ++it;
    auto ins = v.insert(it, 10);

    REQUIRE(*ins == 10);
    REQUIRE(v.size() == 5);

    int expected[] = {5, 10, 15, 20, 25};
    for (int k = 0; k < v.size(); k++) {
        REQUIRE(v.at(k) == expected[k]);
    }
}

TEST_CASE("Erase iterator removes element and shifts the following elements left by 1") {
    Vector<int> v;
    v.push_back(5);
    v.push_back(15);
    v.push_back(20);
    v.push_back(25);

    auto it = v.begin();
    ++it;
    auto ers = v.erase(it);

    REQUIRE(*ers == 20);
    REQUIRE(v.size() == 3);

    int expected[] = {5, 20, 25};
    for (int k = 0; k < v.size(); k++) {
        REQUIRE(v.at(k) == expected[k]);
    }
}

TEST_CASE("Empty vector has begin() equal to end()") {
    Vector<int> v;
    REQUIRE(v.begin() == v.end());
}


