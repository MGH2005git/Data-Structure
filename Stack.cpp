// Mobin Ghorbani
// November 3, 2025
#include <iostream>
#include <stdexcept>

template <typename T>
class Stack{
private:
    T* stack;
    int capacity;
    int point;

public:
    // constructor
    Stack(){
        capacity = 256;
        stack = new T[capacity];
        point = -1;
    }

    Stack(const int &cap){
        capacity = cap;
        stack = new T[capacity];
        point = -1;
    }

    // destructor
    ~Stack(){
        delete[] stack;
    }

    // methods
    void push(const T& data) {
        if(full()) throw std::overflow_error("Stack overflow");
        point++;
        stack[point] = data;
    }

    void pop() {
        if(empty()) throw std::runtime_error("Stack is empty");
        point--;
    }

    T& top(){
        if(empty()) throw std::runtime_error("Stack is empty");
        return stack[point];
    }

    bool contains(const T& value){
        if(empty()) return false;
        for (int i = 0; i < point; i++)
            if(stack[i] == value) return true;
        return false;
    }

    size_t count(const T& value){
        if(empty()) return 0;
        size_t count = 0;
        for (int i = 0; i < point; i++)
            if(stack[i] == value) count++;
        return count;
    }

    void print(){
        if(empty()) {
            std::cout << "Stack is empty" << std::endl;
        } else {
            for (int i = 0; i <= point; ++i)
                std::cout << stack[i] << " -> ";
            std::cout << "end" << std::endl;
        }
    }

    void clear() {
        point = -1;
    }

    bool empty(){
        return point == -1;
    }

    bool full(){
        return point == capacity - 1;
    }

    int size(){
        return point + 1;
    }

    int get_capacity(){
        return capacity;
    }

};

