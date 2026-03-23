//include/matrix.hpp
#pragma once

#include "vector.hpp"
#include <stdexcept>  // std::out_of_range

namespace dsac::array{

class Matrix {
private:
    int rows{0};
    int cols{0};
    dsac::array::Vector<dsac::array::Vector<int>> data;

public:
    /*
    if r < 0 OR c < 0 
        throw std::out_of_range("Negative dimensions");
    rows = r
    cols = c
    for i from 0 to rows-1
        declare row vector of ints
        for j from 0 to cols-1
            append 0 to row  // initialize each element with 0
        append row to data
    */
    Matrix(int r, int c) {
        if (r < 0 || c < 0) {
            throw std::out_of_range("Negative dimensions");
        }
        rows = r;
        cols = c;
        
        for (int i = 0; i < rows; i++) {  
            Vector<int> row;  // declare row vector of ints
            for (int j = 0; j < cols; j++) {
                row.push_back(0);  // append 0 to row
            }
            data.push_back(row);  // append row to data
        }
    }

    //data.at(i).at(j)
    int& operator()(int i, int j) {
        if (i < 0 || i > rows || j < 0 || j >= cols) {  // check if given location is within the matrix
            throw std::out_of_range("Invalid matrix index");  
        }
        return data.at(i).at(j); // returns element at location (i, j)
    }

    // throw std::out_of_range("dimensions must match")
    // result(i, j) = (*this)(i, j) + other(i, j)
    Matrix operator+(Matrix& other) {
        if (rows != other.rows || cols != other.cols) {   // checks if dimensions match before adding
            throw std::out_of_range("Dimensions must match");
        }
        Matrix result(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = (*this)(i, j) + other(i, j); // adds each element of the same index in the two matrices
            }
        }
        return result;
    }

};

}