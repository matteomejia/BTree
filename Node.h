//
// Created by matte on 16/11/2018.
//

#ifndef BTREE_NODE_H
#define BTREE_NODE_H

#include <iostream>

class Node {
public:
    Node **childs; // An array of child pointers
    int *keys;  // An array of keys
    int min_degree;
    int n;
    bool isLeaf;
public:
    Node(int min_degree, bool isLeaf) {
        this->min_degree = min_degree;
        this->isLeaf = isLeaf;

        this->keys = new int[2*min_degree-1];
        this->childs = new Node *[2*min_degree];

        this->n = 0;
    }

    // A function to traverse all nodes in a subtree rooted with this node
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

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k) {
        // Initialize index as index of rightmost element
        int i = n-1;

        // If this is a isLeaf node
        if (isLeaf) {
            // The following loop does two things
            // a) Finds the location of new key to be inserted
            // b) Moves all greater keys to one place ahead
            while (i >= 0 && keys[i] > k) {
                keys[i+1] = keys[i];
                i--;
            }

            // Insert the new key at found location
            keys[i+1] = k;
            n = n+1;
        }
        else // If this node is not isLeaf{
            // Find the child which is going to have the new key
            while (i >= 0 && keys[i] > k) {
                i--;
            }

        // See if the found child is full
        if (childs[i+1]->n == 2*min_degree-1) {
            // If the child is full, then split it
            splitChild(i+1, childs[i+1]);

            // After split, the middle key of childs[i] goes up and
            // childs[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i+1] < k) {
                i++;
            }
        }
        childs[i+1]->insertNonFull(k);
    }

    // A utility function to split the child y of this node. i is index of y in
    // child array C[].  The Child y must be full when this function is called
    void splitChild(int i, Node *y) {
        // Create a new node which is going to store (min_degree-1) keys
        // of y
        Node *z = new Node(y->min_degree, y->isLeaf);
        z->n = min_degree - 1;

        // Copy the last (min_degree-1) keys of y to z
        for (int j = 0; j < min_degree-1; j++) {
            z->keys[j] = y->keys[j + min_degree];
        }

        // Copy the last min_degree children of y to z
        if (!(y->isLeaf)) {
            for (int j = 0; j < min_degree; j++) {
                z->childs[j] = y->childs[j + min_degree];
            }
        }

        // Reduce the number of keys in y
        y->n = min_degree - 1;

        // Since this node is going to have a new child,
        // create space of new child
        for (int j = n; j >= i+1; j--) {
            childs[j + 1] = childs[j];
        }

        // Link the new child to this node
        childs[i + 1] = z;

        // A key of y will move to this node. Find location of
        // new key and move all greater keys one space ahead
        for (int j = n-1; j >= i; j--) {
            keys[j + 1] = keys[j];
        }

        // Copy the middle key of y to this node
        keys[i] = y->keys[min_degree - 1];

        // Increment count of keys in this node
        n = n + 1;
    }

    // A function to search a key in the subtree rooted with this node.
    // returns NULL if k is not present.
    Node *search(int k){
        // Find the first key greater than or equal to k
        int i = 0;
        while (i < n && k > keys[i])
            i++;

        // If the found key is equal to k, return this node
        if (keys[i] == k)
            return this;

        // If key is not found here and this is a leaf node
        if (isLeaf)
            return nullptr;

        // Go to the appropriate child
        return childs[i]->search(k);
    }

};

#endif //BTREE_NODE_H
