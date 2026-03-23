# A8: Vector (Part 2)

## Objective

* In this assignment, you will:
  * Implement a simplified dynamic array class `dsa::array::Vector<T>` (similar to `std::vector`)
  * Use your Vector implementation to build a Matrix class
  * Overload the `+` operator to support matrix addition

## Requirements

* Vector Implementation
  * You may copy the vector code that you submitted in Part 1
  * Add any additional functionality required for this assignment
  * You must not use std::vector anywhere in your implementation.
* Matrix Implementation
  * Implement a Matrix class using your `dsa::array::Vector<T>`
  * Follow the instructions in the starter code in the matrix.hpp
  * Overload the + operator to perform matrix addition



## Starter code

* Clone the repo: https://github.com/naneja/ece3514/tree/main/assignments/a8
* include/array/vector.hpp
* include/array/matrix.hpp
* There are three files for testing
  * test_vector_1.cpp
    * you may copy all of the previous test cases from Part 1 in this
  * test_vector_2.cpp
    * this file is to write new test cases for part 2 of the assignment as per the rubrics
  * test_matrix.cpp
    * this file is to write test cases for matrix operation as per the rubrics
  * Please note \#define CATCH_CONFIG_MAIN should be in only one test file. This has been commented in test_vector_2.cpp and test_matrix.cpp.
* CMakeLists.txt is configured to use all test files

## Submissions:

* Updated repo https://github.com/naneja/ece3514/tree/main/assignments/a8

  * vector.hpp

  * matrix.hpp

  * test files

    * test_vector_1.cpp 
      * test cases from previous assignment A7
    * test_vector_2.cpp 
      * test cases for vector.hpp for this assignment as per the rubrics

    * test_matrix.cpp 
      * test cases for matrix.hpp for this assignment as per the rubrics

  * Please don't submit the build or executable folder [negative two points if submitted]


# Rubrics

* Autograder: 8 Points

  * Instructor test cases: 6 Points
  * Student test cases: 2 Points

* Manual Grading: 12 Points

  * Student Test Cases to cover:
    * at least four different test cases for iterator in 'test'
    * at least four different test cases for const iterator
    * at least four test cases for matrix (including one for addition)

* Negative Two Points for uploading build folder or executable files

  
# ProjA8
