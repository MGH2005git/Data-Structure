#include <iostream>
#include <vector>
/* Written by Mobin Ghorbani */
// December 8, 2025
class RBT {
public:
    struct node {
        int data;
        node *left;
        node *right;
        node *parent;
        bool black;
        node(int val){
            data = val;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            black = false;
        }
    };

    node *root;
    int size;

    // constructor
    RBT(){
        root = nullptr;
        size = 0;
    }

    // BST functions

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

    // RBT functions

    int black_height(node *current){ // bh
        if(!current) return 0;
        node *p = current;
        int count = 0;
        if(p->black) count++;
        count += max(black_height(p->left), black_height(p->right));
        return count;
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

    node *get_uncle(node *current){
        if(!current || !current->parent || !current->parent->parent) return NULL;
        node *father = current->parent;
        node *grandfather = father->parent;
        if(father == grandfather->right) return grandfather->left;
        else return grandfather->right;
    }

    node *get_sibling(node *current) {
        if(!current || !current->parent) return nullptr;
        if(current == current->parent->left)
            return current->parent->right;
        else
            return current->parent->left;
    }

    void insert(int data){
        if(!root){
            root = new node(data);
            root->black = true;
            size++;
            return;
        }
        // find location using BST insertion
        node *p = root;
        node *parent = nullptr;
        while (p != nullptr){
            parent = p;
            if(data == p->data) return;
            if(data > p->data) p = p->right;
            else p = p->left;
        }
        node *newNode = new node(data);
        newNode->parent = parent;
        if(data > parent->data) parent->right = newNode;
        else parent->left = newNode;
        size++;
        fix_insert(newNode);
    }

    void fix_insert(node *current){
        node *parent = nullptr;
        node *grandparent = nullptr;
        node *uncle = nullptr;
        // While parent exists and is RED (violation of Rule 3)
        while(current != root && current->parent != nullptr &&
              !current->parent->black && current->parent->parent != nullptr){

            parent = current->parent;
            grandparent = parent->parent;

            // Case A: Parent is left child of grandparent
            if(parent == grandparent->left){
                uncle = grandparent->right;

                // Case 1: Uncle is RED
                if(uncle != nullptr && !uncle->black){
                    // Recolor
                    parent->black = true;
                    uncle->black = true;
                    grandparent->black = false;

                    // Move up the tree
                    current = grandparent;
                }
                else{
                    // Case 2: Current is right child (triangle shape)
                    if(current == parent->right){
                        current = parent;
                        rotate_left(current);
                        parent = current->parent;  // Update parent after rotation
                    }
                    // Case 3: Current is left child (line shape)
                    parent->black = true;
                    grandparent->black = false;
                    rotate_right(grandparent);
                }
            }
                // Case B: Parent is right child of grandparent (symmetric)
            else{
                uncle = grandparent->left;

                // Case 1: Uncle is RED
                if(uncle != nullptr && !uncle->black){
                    // Recolor
                    parent->black = true;
                    uncle->black = true;
                    grandparent->black = false;

                    // Move up the tree
                    current = grandparent;
                }
                else{
                    // Case 2: Current is left child (triangle shape)
                    if(current == parent->left){
                        current = parent;
                        rotate_right(current);
                        parent = current->parent;  // Update parent after rotation
                    }
                    // Case 3: Current is right child (line shape)
                    parent->black = true;
                    grandparent->black = false;
                    rotate_left(grandparent);
                }
            }
        }
        // Ensure root is BLACK (Rule 2)
        root->black = true;
    }

    void delete_data(int data){
        node *z = search(data);
        if(!z) return;

        node *y = z;  // Node to be deleted
        node *x = nullptr;  // Child of y
        // Determine y (either z or its successor)
        bool y_original_color = y->black;

        if(z->left == nullptr){
            x = z->right;
            transplant(z, z->right);
        }
        else if(z->right == nullptr){
            x = z->left;
            transplant(z, z->left);
        }
        else{
            // Node has two children
            y = successor(z);  // Find in-order successor
            y_original_color = y->black;
            x = y->right;

            if(y->parent == z){
                if(x) x->parent = y;
            }
            else{
                transplant(y, y->right);
                y->right = z->right;
                if(y->right) y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            if(y->left) y->left->parent = y;
            y->black = z->black;
        }

        delete z;
        size--;

        // If the removed node was black, fix the tree
        if(y_original_color){
            fix_delete(x);
        }
    }

    void transplant(node *u, node *v){
        if(!u->parent){
            root = v;
        }
        else if(u == u->parent->left){
            u->parent->left = v;
        }
        else{
            u->parent->right = v;
        }

        if(v){
            v->parent = u->parent;
        }
    }

    void fix_delete(node *x){
        while(x != root && (x == nullptr || x->black)){
            if(x == nullptr) break;

            node *sibling = get_sibling(x);

            if(x == x->parent->left){
                // Case 1: Sibling is RED
                if(sibling && !sibling->black){
                    sibling->black = true;
                    x->parent->black = false;
                    rotate_left(x->parent);
                    sibling = x->parent->right;
                }

                // Case 2: Sibling and both its children are BLACK
                if((!sibling || (sibling->left == nullptr || sibling->left->black) &&
                                (sibling->right == nullptr || sibling->right->black))){
                    if(sibling) sibling->black = false;
                    x = x->parent;
                }
                else{
                    // Case 3: Sibling's right child is BLACK, left child is RED
                    if(sibling->right == nullptr || sibling->right->black){
                        if(sibling->left) sibling->left->black = true;
                        sibling->black = false;
                        rotate_right(sibling);
                        sibling = x->parent->right;
                    }

                    // Case 4: Sibling's right child is RED
                    sibling->black = x->parent->black;
                    x->parent->black = true;
                    if(sibling->right) sibling->right->black = true;
                    rotate_left(x->parent);
                    x = root;  // Terminate loop
                }
            }
            else{
                // Symmetric cases for right child
                sibling = x->parent->left;

                // Case 1: Sibling is RED
                if(sibling && !sibling->black){
                    sibling->black = true;
                    x->parent->black = false;
                    rotate_right(x->parent);
                    sibling = x->parent->left;
                }

                // Case 2: Sibling and both its children are BLACK
                if((!sibling || (sibling->left == nullptr || sibling->left->black) &&
                                (sibling->right == nullptr || sibling->right->black))){
                    if(sibling) sibling->black = false;
                    x = x->parent;
                }
                else{
                    // Case 3: Sibling's left child is BLACK, right child is RED
                    if(sibling->left == nullptr || sibling->left->black){
                        if(sibling->right) sibling->right->black = true;
                        sibling->black = false;
                        rotate_left(sibling);
                        sibling = x->parent->left;
                    }

                    // Case 4: Sibling's left child is RED
                    sibling->black = x->parent->black;
                    x->parent->black = true;
                    if(sibling->left) sibling->left->black = true;
                    rotate_right(x->parent);
                    x = root;  // Terminate loop
                }
            }
        }

        if(x) x->black = true;
    }

    void print(node *current) { // inOrder
        if (!current) return;
        print(current->left);
        std::cout << (current->black ? "B" : "R") << current->data << " ";
        print(current->right);
    }

    void print() {
        print(root);
        std::cout << std::endl;
    }

    bool isLeaf(node *p) {
        if (!p) return false;
        return (p->left == nullptr && p->right == nullptr);
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
    ~RBT() {
        clear(root);
    }
};

