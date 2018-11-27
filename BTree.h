//
// Created by matte on 16/11/2018.
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

#include "node.h"
#include <iostream>

class BTree {
    Node *root;
    int min_degree;
public:
    BTree(int min_degree) {
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

        }
    }

};

#endif //BTREE_BTREE_H
