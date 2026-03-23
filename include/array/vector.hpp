#pragma once
#include <algorithm>     // provides max
#include <stdexcept>     // provides out_of_range exception
#include <utility>

namespace dsac::array {

    template <typename T>
class Vector {
    private:
        int cap{0};
        int sz{0};
        T* data{nullptr};
    public:
        //empty
        Vector() : cap(0), sz(0), data(nullptr) {}   // initially no memory allocated
        
        //capacity
        int capacity() const {
            return cap;
        }

        //how many elements stored
        int size() const {
            return sz;
        }
        
        // True is empty
        bool empty() const {
            return sz == 0;
        }
        
        //element at index when vector is const
        const T& operator[](int i) const {
            return data[i];
        }
        
        //element at index when vector is non-const
        T& operator[](int i) {
            return data[i];
        }
        
        // at function for const
        const T& at(int i) const {
            if (i < 0 || i >= sz)
                throw std::out_of_range("Invalid Index");
            return data[i];
        }
        
        // at function for non const
        T& at(int i) {
            if (i < 0 || i >= sz)
                throw std::out_of_range("Invalid Index");
            return data[i];
        }
        
        // first element
        const T& front() const {
            return data[0];   //first index
        }

        // first element
        T& front() {
            return data[0];
        }
        
        // last element
        const T& back() const {
            return data[sz - 1];  //last index
        }

        // last element
        T& back() {
            return data[sz - 1];
        }
        
        // insert at end
        void push_back(const T& elem) {  
            
            if (sz == cap) { // if the # of elements in the array is at capacity
                reserve(std::max(1, 2*cap)); //allocate double the current capacity if the array is not zero. If zero, increase by 1.
            }

            data[sz++] = elem; //input element at the first free index
            // sz++; increment the # of elements in array
        }

        // remove from end
        // also call shrink
        void pop_back() {
            if (sz == 0) {
                return;
            }

            sz--; //reduces how much of the array is considered active
            shrink(); // checks if capacity needs to be updated
        }

        // insert at index
        void insert(int i, const T& elem) {
            if (i < 0 || i > sz) { // ensure index is within bounds
                throw std::out_of_range("Invalid Index");
            }

            if (sz == cap) { // check if capacity needs to be doubled
                reserve (std::max(1, 2*cap));
            }

            for (int j = sz - 1; j >= i; --j) {  
                data[j + 1] = std::move(data[j]); //move each element up by 1 index, from the index of the last element to the index of the insert
            }
            data[i] = elem; //insert the element in the index i
            sz++; // increment the # of elements in the array
        }

        // removes at index
        // also call shrink
        void erase(int i) {
            if (i < 0 || i >= sz) { // ensure index is within bounds
                throw std::out_of_range("Invalid Index");
            }

            for (int j = i + 1; j < sz; j++) {  
                data[j - 1] = std::move(data[j]); //move each element down by 1 index, from the index of the last element to the index of the insert
            }
            sz--; // decrement the # of elements in the array
            shrink(); // checks if capacity needs to be updated
        }

        //capacity >= minimum
        void reserve(int minimum) {
            if (cap >= minimum) { //there is enough capacity, so no need to allocate more space
                return;
            }

            T* temp = new T[minimum]; //creates a temporary array with the min amt of space needed for the next operation
            for (int i = 0; i < sz; i++) {
                temp[i] = std::move(data[i]); //moves the values from data to temp then deallocates memory from data
            }
            delete[] data; //free the memory from the old data array
            data = temp; //update the data with new memory
            cap = minimum; //update capacity with new amt of memory allocated in updated data array
        }

        // Rule of Five Implementation

        Vector(const Vector& other) : cap(0), sz(0), data(nullptr) {   // Copy Constructor
            clone(other); 
        }

        Vector& operator=(const Vector& other) { // Copy Assignment
            if (this != &other) {
                delete[] data;
                clone(other);
            }
            return *this;
        }

        Vector(Vector&& other) : cap(0), sz(0), data(nullptr) { // Move Constructor
            transfer(other);
        }

        Vector& operator=(Vector&& other) {
            if (this != &other) {
                delete[] data;
                transfer(other);
            }
            return *this;
        }

        ~Vector() { delete[] data; }
    
    private:
        void clone(const Vector& other) {
            cap = other.cap;
            sz = other.sz;
            data = new T[cap];
            for (int k = 0; k < sz; k++) {
                data[k] = other.data[k];
            }
        }

        void transfer(Vector& other) {
            cap = other.cap;
            sz = other.sz;
            data = other.data;
            other.cap = other.sz = 0;
            other.data = nullptr;
        }

    public:
        class iterator {
            friend class Vector; // for Vector insert & erase
            private:
                Vector* vec;    // maintains a connection to the specific container instacne that created the iterator
                int ind;        // index within the vector
            
            public:
                iterator(Vector* v = nullptr, int i = -1) : vec{v}, ind{i} {}
                T& operator*() const {
                    return (*vec)[ind]; // returns a reference to the element at position ind be dereferencing the container pointer and indexing it
                }
                T* operator->() const {
                    return &(*vec)[ind]; // returns the address of the current element so that built-in -> can access member variables or functions
                }
                iterator& operator++() { // prefix increment ++it
                    ++ind;
                    return *this; // advances iterator and returns reference to updated object
                }
                iterator operator++(int) { // postfix increment it++
                    iterator old(*this);
                    ++ind;
                    return old; // returns old iterator value, then advances
                }
                iterator& operator--() { // prefix decrement --it
                    --ind; 
                    return *this; // moves iterator backward and returns reference
                }
                iterator operator--(int) { // postfix decrement it--
                    iterator old(*this);
                    --ind;
                    return old; // returns old iterator value, then moves backward
                }
                bool operator==(iterator rhs) const {
                    return vec == rhs.vec && ind == rhs.ind; // iterators are equal if they refer to the same container and the same position within that container
                }
                bool operator!=(iterator rhs) const {
                    return !(*this == rhs); // Inequality defined in terms of equality to avoid duplication
                }
        };

        class const_iterator {
            private:
                const Vector* vec;
                int ind;                   // index within the vector
            
            public:
                const_iterator(const Vector* v = nullptr, int i = -1) : vec{v}, ind{i} {}
                const T& operator*() const {
                    return (*vec)[ind];
                }
                const T* operator->() const {
                    return &(*vec)[ind];
                }
                const_iterator& operator++() {
                    ++ind;
                    return *this;
                }
                const_iterator operator++(int) {
                    const_iterator old(*this);
                    ++ind;
                    return old;
                }
                const_iterator& operator--() {
                    --ind; 
                    return *this; 
                }
                const_iterator operator--(int) {
                    const_iterator old(*this);
                    --ind;
                    return old;
                }
                bool operator==(const_iterator rhs) const {
                    return vec == rhs.vec && ind == rhs.ind;
                }
                bool operator!=(const_iterator rhs) const {
                    return !(*this == rhs);
                }
        };

        iterator begin() {
            return iterator(this, 0);
        }
        iterator end() {
            return iterator(this, sz);
        }
        const_iterator begin() const {
            return const_iterator(this, 0);
        }
        const_iterator end() const {
            return const_iterator(this, sz);
        }

        iterator insert(iterator it, const T& elem) {
            insert(it.ind, elem); // calls the index-based version
            return it; // new element was placed at the given index
        }

        iterator erase(iterator it) {
            erase(it.ind); // erases the element at the iterator position
            return it; // element after removed has been shifted one position to the left
        }

        // called by other functions to reduce cap by half 
        // when sz <= cap/4 
        void shrink() {

            if (cap <= 1) {
                return;
            }

            if (sz <= cap/4) {
                int lessCap = cap / 2; // reduces cap by half when sz is a fourth of the current cap

                if (lessCap < 1) {
                    lessCap = 1;
                }

                T* temp = new T[lessCap]; //creates a temporary array with half the cap of the current array
                for (int i = 0; i < sz; i++) {
                    temp[i] = std::move(data[i]); //moves the values from data to temp then deallocates memory from data
                }
                delete[] data; //free the memory from the old data array
                data = temp; //update the data with new memory
                cap = lessCap; //update capacity with new amt of memory allocated in updated data array
            }
        }
        
        // explicitly reduce the cap to sz and keep at least 1 slot
        void shrink_to_fit() {
            int lessCap = std::max(1, sz); // selects the current # of elements unless the sz is 0, then leaves 1 slot

            T* temp = new T[lessCap]; //creates a temp array of sz + 1
            for (int i = 0; i < sz; i++) {
                temp[i] = std::move(data[i]); // place current elements in temp array and deallocate from data
            }
            delete[] data; //free the memory from the old data array
            data = temp; //update data array with explicitly sized temp array
            cap = lessCap; //update data array capacity with new amt of memory allocated in temp array
        }
    
}; // Vector class

}  // namespace dsac::array
