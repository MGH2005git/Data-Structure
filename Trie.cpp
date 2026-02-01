#include <iostream>
#include <string>
/* English Dictionary Trie*/
#define N 26

class Trie{
public:
    struct node {
        node *child[N];
        node *parent;
        bool valid;
        char c;
        std::string desc;
        node(){
            for (int i = 0; i < N; ++i) {
                child[i] = nullptr;
            }
            parent = nullptr;
            valid = false;
            c = '0';
        }
    };
private:
    node *root;

    static bool isleaf(node *p){
        if(!p) return false;
        for (int i = 0; i < N; ++i) {
            if(p->child[i] != nullptr) return false;
        }
        return true;
    }

public:
    // constructor
    Trie(){
        root = new node();
    }

    void add_word(const std::string &word){
        for (char c:word)
            if(tolower(c) < 'a' || tolower(c) > 'z') return;
        node *p = root;
        for (char c:word){
            int index = tolower(c) - 'a';
            if(p->child[index] == nullptr){
                p->child[index] = new node();
                p->child[index]->parent = p;
                p->child[index]->c = tolower(c);
            }
            p = p->child[index];
        }
        p->valid = true;
    }

    node *search(const std::string &word){
        for (char c:word)
            if(tolower(c) < 'a' || tolower(c) > 'z') return nullptr;
        node *p = root;
        for (char c:word){
            int index = tolower(c) - 'a';
            if(p->child[index] == nullptr) return nullptr;
            p = p->child[index];
        }
        return p;
    }

    void delete_word(const std::string &word){
        for (char c:word)
            if(tolower(c) < 'a' || tolower(c) > 'z') return;
        node *p = search(word);
        if(p == nullptr || !p->valid) return; // word not found
        p->valid = false;
        while(p != root){
            if(isleaf(p) && !p->valid){
                node *parent = p->parent;
                int index = p->c - 'a';
                delete p;
                parent->child[index] = nullptr;
                p = parent;
            } else {
                break;
            }
        }
    }

};

