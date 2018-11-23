//
// Created by matte on 16/11/2018.
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

#include "Node.h"

class BTree {
    Node *root;
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

    Node* search(int k)
    {
        if(root == nullptr) {
            return nullptr;
        }else {
            return root->search(k);
        }
    }

    // The main function that inserts a new key in this B-Tree
    void insert(int k) {
        // If tree is empty
        if (root == nullptr) {
            // Allocate memory for root
            root = new Node(min_degree, true);
            root->keys[0] = k;  // Insert key
            root->n = 1;  // Update number of keys in root
        } else // If tree is not empty{
            // If root is full, then tree grows in height
        if (root->n == 2*min_degree-1) {
            // Allocate memory for new root
            Node *s = new Node(min_degree, false);

            // Make old root as child of new root
            s->childs[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0] < k) {
                i++;
            }
            s->childs[i]->insertNonFull(k);

            // Change root
            root = s;
        } else {// If root is not full, call insertNonFull for root
            root->insertNonFull(k);
        }
    }
};

#endif //BTREE_BTREE_H
