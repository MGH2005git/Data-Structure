// Mobin Ghorbani 40332360
// November 3, 2025
#include <iostream>
#include <stdexcept>

template <typename T> // Generic type programming
class DoubleLinkedList {

private:
    struct node {
        T data;
        node *next;
        node *prev;
        node(const T &value){
            data = value;
            next = nullptr;
            prev = nullptr;
        }
    };

    node *head;
    node *tail;
    size_t size;

public:

    // constructor
    DoubleLinkedList(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // Destructor
    ~DoubleLinkedList() {
        clear();
    }

    // methods
    void add_last(const T& value){
        node *newnode = new node(value);
        if(empty()){
            head = tail = newnode;
        } else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
        size++;
    }

    void add_first(const T& value){
        node *newnode = new node(value);
        if(empty()){
            head = tail = newnode;
        } else {
            newnode->next = head;
            head->prev = newnode;
            head = newnode;
        }
        size++;
    }

    void delete_last(){
        if(empty()) throw std::runtime_error("List is empty");
        if(head == tail){
            delete head;
            head = tail = nullptr;
            size = 0;
        } else {
            node *p = tail->prev;
            delete tail;
            p->next = nullptr;
            tail = p;
            size--;
        }
    }

    void delete_first(){
        if(empty()) throw std::runtime_error("List is empty");
        if(head == tail){
            delete head;
            head = tail = nullptr;
            size = 0;
        } else {
            node *p = head->next;
            p->prev = nullptr;
            delete head;
            head = p;
            size--;
        }
    }

    T& at(const size_t &index){
        if(index >= size) throw std::out_of_range("Index out of range");
        node *p = head;
        size_t i = 0;
        while (i < index){
            p = p->next;
            i++;
        }
        return p->data;
    }

    void insert_at(const size_t &index, const T& value){
        if(index > size) throw std::out_of_range("Index out of range");
        if(index == 0) return add_first(value);
        if(index == size) return add_last(value);
        node *newnode = new node(value);
        node *p = head;
        size_t i = 0;
        while(i < index - 1) i++, p = p->next;
        node *next = p->next;
        p->next = newnode;
        newnode->prev = p;
        newnode->next = next;
        next->prev = newnode;
        size++;
    }

    void delete_node(const size_t &index){
        if(empty()) throw std::runtime_error("List is empty");
        if(index >= size) throw std::out_of_range("Index out of range");
        if(index == 0) return delete_first();
        if(index == size - 1) return delete_last();
        node *p = head;
        size_t i = 0;
        while (i < index - 1) i++, p = p->next;
        node *target = p->next;
        node *next = target->next;
        delete target;
        p->next = next;
        next->prev = p;
    }

    bool contains(const T& value){
        if(empty()) return false;
        node *p = head;
        while (p != nullptr){
            if(p->data == value) return true;
            p = p->next;
        }
        return false;
    }

    int find(const T& value){
        if(empty()) return -1;
        int index = 0;
        node *p = head;
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
        node *p = head;
        while (p != nullptr){
            if(p->data == value) count++;
            p = p->next;
        }
        return count;
    }

    void print(){
        if(empty()){
            std::cout << "List is empty" << std::endl;
            return;
        }
        node *p = head;
        std::cout << "null ";
        while(p != nullptr){
            std::cout << p->data << " <-> ";
            p = p->next;
        }
        std::cout << "null" << std::endl;
    }

    bool empty(){
        return size == 0;
    }

    void clear(){
        while (!empty()) delete_first();
    }

    // getters
    size_t get_size(){
        return size;
    }

    T& get_head(){
        if(empty()) throw std::runtime_error("List is empty");
        return head->data;
    }

    T& get_tail(){
        if(empty()) throw std::runtime_error("List is empty");
        return tail->data;
    }

};

