//
// Created by matte on 16/11/2018.
//

// childs++ program for B-Tree insertion

#include<iostream>
#include "BTree.h"

using namespace std;

int main() {/*
    BTree t(3); //El valor es el grado minimo
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of the constucted tree is ";
    t.traverse();

    int k = 6;
    if (t.search(k) != nullptr){
        cout << "\nPresent";
     }else {
        cout << "\nNot Present";
    }

    k = 15;
    if (t.search(k) != nullptr){
        cout << "\nPresent";
    }else {
        cout << "\nNot Present";
    }*/

    BTree t(2); //El valor es el grado minimo
    t.insert(10);
    t.insert(20);
    t.insert(30);
    t.insert(40);
    t.insert(50);
    t.insert(60);
    t.insert(70);
    t.insert(80);
    t.insert(90);
    t.insert(100);

    t.traverse();

    return 0;
}