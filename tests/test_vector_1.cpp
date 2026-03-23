// test_vector.cpp
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <stdexcept> //for out_of_range exception
#include "array/vector.hpp"

using dsac::array::Vector; // using statement allows me to use Vector instead of writing the full namespace from the header file

TEST_CASE("Default constructor creates empty vector", "[tag]") {
    dsac::array::Vector<int> v;
    bool ok = (v.size() == 0) && (v.capacity() == 0) && v.empty();

    REQUIRE(ok);
}

TEST_CASE("Check capacity, size, and empty with default no values") {
    Vector<int> v;

    REQUIRE(v.capacity() == 0);
    REQUIRE(v.size() == 0);
    REQUIRE(v.empty() == true);
}

TEST_CASE("Check operator[] and at() for const and non-const") {
    Vector<int> v;

    for (int i{0}; i < 5; ++i) 
        v.push_back(i); // 0, 1, 2, 3, 4
    
    //check non-const operator[]
    REQUIRE(v[0] == 0);
    REQUIRE(v[4] == 4);

    //check non-const at()
    v[1] = 30;
    REQUIRE(v.at(1) == 30);

    //check const operator[]
    const Vector<int>& cv = v;
    REQUIRE(cv[3] == 3);
    REQUIRE(cv[1] == 30);
}

TEST_CASE("Check out of bounds throws for at()") {
    Vector<int> v;

    REQUIRE_THROWS_AS(v.at(6), std::out_of_range);
    REQUIRE_THROWS_AS(v.at(-3), std::out_of_range);
}

TEST_CASE("Check front() and back() for const and non-const") {
    Vector<int> v;

    for (int i{0}; i < 5; ++i) 
        v.push_back(i * 3); // 0, 3, 6, 9, 12

    REQUIRE(v.front() == 0);
    REQUIRE(v.back() == 12);

    v.push_back(15);
    REQUIRE(v.front() == 0);
    REQUIRE(v.back() == 15);
}

TEST_CASE("Check push_back() that cap is never less than sz and correct order") {
    Vector<int> v;

    for (int i = 0; i < 15; i++) {
       v.push_back(i);
       REQUIRE(v.size() == i + 1);
       REQUIRE(v.capacity() >= v.size()); // ensure capacity stays larger than # of elements
    }
}

TEST_CASE("Check pop_back() that size decreases but stops on empty vector") {
    Vector<int> v;

    //check empty
    v.pop_back();
    REQUIRE(v.empty());
    REQUIRE(v.size() == 0);

    //check with values
    for (int i{0}; i < 5; ++i) 
        v.push_back(i * 3); // 0, 3, 6, 9, 12

    v.pop_back();
    REQUIRE(v.size() == 4);
    REQUIRE(v.back() == 9);

    v.pop_back();
    v.pop_back();
    REQUIRE(v.size() == 2);
    REQUIRE(v.back() == 3);
}

TEST_CASE("Check insert() and erase() that they have maintain order correctly") {
    Vector<int> v;

    for (int i{0}; i < 5; ++i) 
        v.push_back(i * 3); // 0, 3, 6, 9, 12
    
    v.insert(2, 30); // 0, 3, 30, 6, 9, 12
    REQUIRE(v.size() == 6);
    REQUIRE(v.at(2) == 30);
    

    v.erase(4); // 0, 3, 30, 6, 12
    REQUIRE(v.size() == 5);
    REQUIRE(v.at(4) == 12);

    //Check out of bounds cases
    int expect[] = {0, 3, 30, 6, 12};
    REQUIRE(v.size() == 5);

    REQUIRE_THROWS_AS(v.insert(12, 40), std::out_of_range);
    REQUIRE_THROWS_AS(v.insert(-5, 8), std::out_of_range);

    REQUIRE_THROWS_AS(v.erase(25), std::out_of_range);
    REQUIRE_THROWS_AS(v.erase(-3), std::out_of_range);

    REQUIRE(v.size() == 5); // stays the same
    for (int i{0}; i < 5; ++i) //Checks that no changes were made to data
        REQUIRE(v.at(i) == expect[i]);

    REQUIRE(v.capacity() >= v.size()); //Check that capacity is still greater than size
}

TEST_CASE("Check shrink() that it correctly halves capacity when size is a fourth of the capacity") {
    Vector<int> v;

    for (int i{0}; i < 36; ++i) //Start array
        v.push_back(i);
    REQUIRE(v.size() == 36);
    REQUIRE(v.capacity() >= v.size());

    const int currCap = v.capacity();
    for (int i{0}; i < 30; ++i) 
        v.pop_back();
    REQUIRE(v.size() == 6);   //reduce size to cause shrink to happen since size is less than 9
    REQUIRE(v.capacity() <= currCap/2); //check that capacity is less than half the previous capacity
    
    //Check that it still holds the correct values in the correct order
    for (int i{0}; i < 6; ++i) 
        REQUIRE(v.at(i) == i);

    REQUIRE(v.capacity() >= v.size()); //Check that capacity is still greater than size
}

TEST_CASE("Check shrink_to_fit that it correctly changes capacity to size (1 free slot)") {
    Vector<int> v;

    //Check empty vector returns cap of 1
    v.shrink_to_fit();
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 1);

    //Check with values
    for (int i{0}; i < 5; ++i) 
        v.push_back(i * 3); // 0, 3, 6, 9, 12

    //use reserve to allocate space, then do shrink_to_fit and check size/capacity
    v.reserve(50);
    REQUIRE(v.capacity() >= 50);
    v.shrink_to_fit();
    REQUIRE(v.capacity() == v.size());

    //Check that it still holds the correct values in the correct order
    int expect[] = {0, 3, 6, 9, 12};
    for (int i{0}; i < 5; ++i) 
        REQUIRE(v.at(i) == expect[i]);

    REQUIRE(v.capacity() >= v.size()); //Check that capacity is still greater than size
}