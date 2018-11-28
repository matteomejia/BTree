//
// Created by matte on 16/11/2018.
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

#include "node.h"
#include <iostream>

class BTree {
public:
    Node *root;
    int min_degree;
public:
    explicit BTree(int min_degree) {
        this->root = nullptr;
        this->min_degree = min_degree;
    }

    void traverse() {
        if(root != nullptr) {
            root->traverse();
        }
    }

    Node *search(int key) {
        if(root == nullptr) {
            return nullptr;
        }else {
            root->search(key);
        }
    }

    void insert(int key) {
        Node *node = root;

        if(root == nullptr) {
            root = new Node(true, min_degree);
            root->keys[0] = key;
            root->nkeys = 1;
        }
        else{
            if(root->is_full()){
                Node * new_root = new Node(false, min_degree);
                new_root->childs[0] = root;
                new_root->split_child(0);
                new_root->insert(key);
                root = new_root;
            }
            else{
                root->insert(key);
            }
        }
    }

};

#endif //BTREE_BTREE_H
