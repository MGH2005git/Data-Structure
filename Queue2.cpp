// Mobin Ghorbani 40332360
// November 3, 2025
// Queue with linked list
#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {  // Queue with linked list
private:
    struct node {
        T data;
        node *next;
        node(const T &value){
            data = value;
            next = nullptr;
        }
    };
    node *front;
    node *back;
    size_t size;

public:
    // constructor
    Queue() {
        front = back = nullptr;
        size = 0;
    }

    // Destructor
    ~Queue() {
        clear();
    }

    // methods
    void enqueue(const T& value){
        node *newnode = new node(value);
        if(empty()){
            front = back = newnode;
        } else {
            back->next = newnode;
            back = newnode;
        }
        size++;
    }

    void dequeue(){
        if(empty()) throw std::runtime_error("Queue is empty");
        if(size == 1){
            delete front;
            front = back = nullptr;
            size = 0;
        } else {
            node *p = front->next;
            delete front;
            front = p;
            size--;
        }
    }

    T& at(const size_t &index){
        if(index >= size) throw std::out_of_range("Index out of range");
        node *p = front;
        size_t i = 0;
        while (i < index){
            p = p->next;
            i++;
        }
        return p->data;
    }

    bool contains(const T& value){
        if(empty()) return false;
        node *p = front;
        while (p != nullptr){
            if(p->data == value) return true;
            p = p->next;
        }
        return false;
    }

    int find(const T& value){
        if(empty()) return -1;
        int index = 0;
        node *p = front;
        while (p != nullptr){
            if(p->data == value) return index;
            p = p->next;
            index++;
        }
        return -1;
    }

    size_t count(const T& value){
        if(empty()) return 0;
        size_t count = 0;
        node *p = front;
        while (p != nullptr){
            if(p->data == value) count++;
            p = p->next;
        }
        return count;
    }

    void print(){
        if(empty()){
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        node *p = front;
        while(p != nullptr){
            std::cout << p->data << " - ";
            p = p->next;
        }
    }

    bool empty(){
        return size == 0;
    }

    void clear(){
        while (!empty()) dequeue();
    }

    // getters
    size_t get_size(){
        return size;
    }

    T& get_front(){
        return front;
    }

    T& get_back(){
        return back;
    }

};

