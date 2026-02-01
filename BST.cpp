#include <iostream>
#include <vector>
/* Written by Mobin Ghorbani */
// December 8, 2025
class BST {
public:
    struct node {
        int data;
        node *left;
        node *right;
        node *parent;
        node(int val){
            data = val;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }
    };

    node *root;
    int size;

    // constructor
    BST(){
        root = nullptr;
        size = 0;
    }

    int max() {
        if (size == 0) return 0;
        node *p = root;
        while (p->right != nullptr) p = p->right;
        return p->data;
    }

    int min() {
        if (size == 0) return 0;
        node *p = root;
        while (p->left != nullptr) p = p->left;
        return p->data;
    }

    node *search(node *current, int data) {
        if (!current) return nullptr;
        if (current->data == data) return current;
        if (data > current->data) return search(current->right, data);
        return search(current->left, data);
    }

    node *search(int data) {
        node *p = root;
        while (p != nullptr) {
            if (p->data == data) return p;
            if (data > p->data) p = p->right;
            else p = p->left;
        }
        return nullptr;
    }

    void print(node *current) { // inOrder
        if (!current) return;
        print(current->left);
        std::cout << current->data << " ";
        print(current->right);
    }

    void print() {
        print(root);
        std::cout << std::endl;
    }

    void addVector(std::vector<int> &v, node *current) { // inOrder
        if (!current) return;
        addVector(v, current->left);
        v.push_back(current->data);
        addVector(v, current->right);
    }

    std::vector<int> getlist() {
        std::vector<int> v;
        addVector(v, root);
        return v;
    }

    bool isLeaf(node *p) {
        if (!p) return false;
        return (p->left == nullptr && p->right == nullptr);
    }

    void insert(int data) {
        if (!root) {
            root = new node(data);
            size++;
            return;
        }
        node *p = root;
        while(true){
            if(p->data == data) return;
            if(data > p->data){
                if(!p->right){
                    p->right = new node(data);
                    p->right->parent = p;
                    break;
                }
                p = p->right;
            } else {
                if(!p->left){
                    p->left = new node(data);
                    p->left->parent = p;
                    break;
                }
                p = p->left;
            }
        }
        size++;
    }

    node* findMin(node* n) {
        while (n->left != nullptr) n = n->left;
        return n;
    }

    node *findMax(node *n){
        while (n->right != nullptr) n = n->right;
        return n;
    }

    node *rotate_left(node *current){
        if(!current) return nullptr;
        if(!current->right) return current;
        node *x = current;
        node *y = current->right;
        node *father = x->parent;

        x->right = y->left;
        y->left = x;
        if(father){
            if(father->right == x) father->right = y;
            else father->left = y;
        }
        y->parent = father;
        x->parent = y;
        if(x == root) root = y;
        return y;
    }

    node *rotate_right(node *current){
        if(!current) return nullptr;
        if(!current->left) return current;
        node *y = current;
        node *x = current->left;
        node *father = y->parent;

        y->left = x->right;
        x->right = y;
        if(father){
            if(father->left == y) father->left = x;
            else father->right = x;
        }
        x->parent = father;
        y->parent = x;
        if(y == root) root = x;
        return x;
    }

    Anonymous, [1/31/2026 9:46 PM]
    node *successor(node *current){
        if(!current) return nullptr;
        node *p = current;
        if(p->right != nullptr){
            // leftmost node in the right subtree
            p = p->right;
            while(p->left != nullptr) p = p->left;
            return p;
        } else {
            // go up until node is its parents left child
            node *p = current->parent;
            node *child = current;
            while(p != nullptr && child == p->right){
                child = p;
                p = p->parent;
            }
            return p;
        }
    }

    node *predecessor(node *current){
        if(!current) return nullptr;
        node *p = current;
        if(p->left != nullptr){
            // rightmost node in the left child
            p = p->left;
            while(p->right != nullptr) p = p->right;
            return p;
        } else {
            // go up until node is its parents right child
            node *p = current->parent;
            node *child = current;

            while(p != nullptr && child == p->left){
                child = p;
                p = p->parent;
            }
            return p;
        }
    }

    void deleteNode(node *target){
        if(!target) return;
        // Leaf node
        if(isLeaf(target)){
            if(target->parent){
                if(target->parent->left == target)
                    target->parent->left = nullptr;
                else
                    target->parent->right = nullptr;
            } else {
                root = nullptr;
            }
            delete target;
            size--;
            return;
        }
        // one child
        if(target->left == nullptr){
            node* rightChild = target->right;
            // Update parent
            if(target->parent){
                if(target->parent->left == target)
                    target->parent->left = rightChild;
                else
                    target->parent->right = rightChild;
            } else {
                root = rightChild;  // Deleting root
            }
            // Update child's parent pointer
            if(rightChild) rightChild->parent = target->parent;
            delete target;
            size--;
            return;
        }
        // node has only left child
        if(target->right == nullptr){
            node* leftChild = target->left;
            // Update parent
            if(target->parent){
                if(target->parent->left == target)
                    target->parent->left = leftChild;
                else
                    target->parent->right = leftChild;
            } else {
                root = leftChild;  // Deleting root
            }
            // Update child's parent pointer
            if(leftChild) leftChild->parent = target->parent;
            delete target;
            size--;
            return;
        }
        // node has two children
        node* s = successor(target);
        // Copy successor's data to target
        target->data = s->data;
        deleteNode(s);
    }

    void deleteRoot(){
        if(!root) return;
        deleteNode(root);
    }

    void deleteValue(int data) {
        node* target = search(data);
        if(target) {
            deleteNode(target);
        }
    }

    void clear(node* current) { // postfix
        if (!current) return;
        clear(current->left);
        clear(current->right);
        delete current;
    }

    bool empty(){
        return size == 0;
    }

    int getSize(){
        return size;
    }

    // Destructor
    ~BST() {
        clear(root);
    }
};

