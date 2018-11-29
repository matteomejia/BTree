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

    ~Node() = default;

    void traverse() {
        int i = 0;

        std::cout<<"keys:";
        for(i = 0; i < nkeys; ++i) {
            std::cout << " " << keys[i];
        }

        if(!isLeaf) {
            for (i = 0; i < nkeys + 1; ++i) {
                std::cout << "\nHijo " << i << ":\n";
                childs[i]->traverse();
            }
        }
    }

    Node *search(int key) {
        int count = 0;
        while(count < nkeys && key > keys[count]) {
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

    Node insert(int key){
        int count = 0;
        while(count < nkeys && key > keys[count]) {
            count++;
        }

        if(isLeaf && !is_full()) {
            int temp = 0;
            for(;count<2 * min_degree - 1;count++){
                temp = keys[count];
                keys[count] = key;
                key = temp;
            }
            nkeys++;
        }
        else if(!isLeaf) {
            childs[count]->insert(key);
        }
    }

    bool is_full(){
        return nkeys >= 2 * min_degree - 1;
    }

    void split_child(int pos_node_full){
        Node * node_izq, *node_der;
        node_izq = new Node (childs[pos_node_full]->isLeaf, min_degree);
        node_der = new Node (childs[pos_node_full]->isLeaf, min_degree);
        for(int i = 0; i < min_degree - 1; i++){
            node_izq->keys[i] = childs[pos_node_full]->keys[i];
            node_der->keys[i] = childs[pos_node_full]->keys[i+min_degree];
        }
        if(!childs[pos_node_full]->isLeaf){
            for(int i = 0; i < min_degree; i++){
                node_izq->childs[i] = childs[pos_node_full]->childs[i];
                node_der->childs[i] = childs[pos_node_full]->childs[i+min_degree];
            }
        }

        node_izq->nkeys = min_degree-1;
        node_der->nkeys = min_degree-1;

        if(nkeys>0) {
            for (int i = nkeys - 1; i >= pos_node_full; i--) {
                keys[i + 1] = keys[i];
                childs[i + 2] = childs[i+1];
            }
        }

        keys[pos_node_full] = childs[pos_node_full]->keys[min_degree - 1];
        delete childs[pos_node_full];
        childs[pos_node_full] = node_izq;
        childs[pos_node_full + 1] = node_der;
        nkeys++;
    }
};

#endif //BTREE_NODE_H
