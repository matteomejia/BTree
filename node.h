//
// Created by matte on 16/11/2018.
//

#ifndef BTREE_NODE_H
#define BTREE_NODE_H

#include <iostream>

class Node {
public:
    int *keys;
    bool isLeaf;
    int min_degree;
    int nkeys;
    Node **childs;
public:
    Node(bool isLeaf, int min_degree) {
        this->min_degree = min_degree;
        this->isLeaf = isLeaf;

        this->keys = new int[2 * min_degree - 1];
        this->childs = new Node *[2 * min_degree];

        this->nkeys = 0;
    }

    void traverse() {
        int i = 0
        for(i = 0; i < nkeys; ++i) {
            if(!isLeaf) {
                childs[i]->traverse();
            }
            std::cout << " " << keys[i];
        }

        if(!isLeaf) {
            childs[i]->traverse();
        }
    }

    Node *search(int key) {
        int count = 0;
        while(count < n && key > keys[count]) {
            count++;
        }

        if(keys[count] == key) {
            return this;
        }

        if(isLeaf) {
            return nullptr;
        }

        return childs[count]->search(key);
    }
};

#endif //BTREE_NODE_H
