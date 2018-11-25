//
// Created by matte on 16/11/2018.
//

#ifndef BTREE_NODE_H
#define BTREE_NODE_H

#include <iostream>

class node {
public:
    node **childs; //array de hijos
    int *keys;  //array de llaves
    int min_degree; //grado minimo
    int n;  //numero de llaves
    bool isLeaf;    //booleano si es hoja
public:
    node(int min_degree, bool isLeaf) {
        this->min_degree = min_degree;
        this->isLeaf = isLeaf;
        this->keys = new int[2 * min_degree - 1];
        this->childs = new node * [2 * min_degree];
        this->n = 0;
    }

    void traverse() {
        int i;
        for (i = 0; i < n; i++) {
            if (!isLeaf) {
                childs[i]->traverse();
            }
            std::cout << " " << keys[i];
        }

        if (!isLeaf) {
            childs[i]->traverse();
        }
    };

    void insertNonFull(int key) {
        int i = n-1;

        if (isLeaf) {
            while (i > -1 && keys[i] > key) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
            n = n + 1;
        }
        else {
            while (i > -1 && keys[i] > key) {
                i--;
            }
        }

        if (childs[i+1]->n == 2*min_degree-1) {
            split(i + 1, childs[i + 1]);

            if (keys[i+1] < key) {
                i++;
            }
        }
        childs[i+1]->insertNonFull(key);
    }

    void split(int i, node *y) {
        node *x = new node(y->min_degree, y->isLeaf);
        x->n = min_degree - 1;

        for (int j = 0; j < min_degree-1; j++) {
            x->keys[j] = y->keys[j + min_degree];
        }

        if (!(y->isLeaf)) {
            for (int j = 0; j < min_degree; j++) {
                x->childs[j] = y->childs[j + min_degree];
            }
        }

        y->n = min_degree - 1;

        for (int j = n; j >= i+1; j--) {
            childs[j + 1] = childs[j];
        }

        childs[i + 1] = x;

        for (int j = n-1; j >= i; j--) {
            keys[j + 1] = keys[j];
        }

        keys[i] = y->keys[min_degree - 1];

        n = n + 1;
    }


    node *search(int key){
        int i = 0;
        while (i < n && key > keys[i]) {
            i++;
        }

        if (keys[i] == key) {
            return this;
        }

        if (isLeaf) {
            return nullptr;
        }

        return childs[i]->search(key);
    }

};

#endif //BTREE_NODE_H
