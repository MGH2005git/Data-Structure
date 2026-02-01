// Mobin Ghorbani 40332360
// November 3, 2025
#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
private:
    T* queue;
    int first;
    int last;
    int capacity;
    int size;

public:
    // constructor
    Queue() {
        capacity = 256;
        queue = new T[capacity];
        first = last = -1;
        size = 0;
    }

    Queue(const int &cap) {
        capacity = (cap < 0) ? 256 : cap;
        queue = new T[capacity];
        first = last = -1;
        size = 0;
    }

    // destructor
    ~Queue() {
        delete[] queue;
    }

    // methods
    void enqueue(const T& data) {
        if(full()) throw std::overflow_error("Queue is full");
        if(empty()) {
            first = last = 0;
        } else {
            last = (last + 1) % capacity;
        }
        queue[last] = data;
        size++;
    }

    void dequeue() {
        if(empty()) throw std::runtime_error("Queue is empty");
        if(size == 1) {
            first = last = -1;
        } else {
            first = (first + 1) % capacity;
        }
        size--;
    }

    bool empty(){
        return size == 0;
    }

    bool full(){
        return size == capacity;
    }

    // getters
    int get_size(){
        return size;
    }

    int get_capacity(){
        return capacity;
    }

    T& front() {
        if(empty()) throw std::runtime_error("Queue is empty");
        return queue[first];
    }

    T& back() {
        if(empty()) throw std::runtime_error("Queue is empty");
        return queue[last];
    }

};

