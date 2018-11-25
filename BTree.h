//
// Created by matte on 16/11/2018.
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

#include "node.h"

class BTree {
    node *root;
    int min_degree;
public:
    BTree(int min_degree) {
        this->root = nullptr;
        this->min_degree = min_degree;
    }

    void traverse()
    {
        if (root != nullptr){
            root->traverse();
        }
    }

    node* search(int key)
    {
        if(root == nullptr) {
            return nullptr;
        }else {
            return root->search(key);
        }
    }

    void insert(int key) {
        if (root == nullptr) {
            root = new node(min_degree, true);
            root->keys[0] = key;
            root->n = 1;
        } else
        if (root->n == 2*min_degree-1) {
            node *s = new node(min_degree, false);

            s->childs[0] = root;

            s->split(0, root);

            int i = 0;
            if (s->keys[0] < key) {
                i++;
            }
            s->childs[i]->insertNonFull(key);

            root = s;
        } else {
            root->insertNonFull(key);
        }
    }
};

#endif //BTREE_BTREE_H
