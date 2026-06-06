// --------------------------------- bstree.h ----------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares a binary search tree that stores Movie pointers. Comparison
//          is delegated to Movie::operator< so one BSTree implementation serves
//          all three genre sort orders. Each tree owns its Movie objects and
//          deletes them in makeEmpty().
// ----------------------------------------------------------------------------

#pragma once
#include <iostream>
#include "movie.h"

class BSTree {
public:
    BSTree();
    ~BSTree();  // calls makeEmpty()

    bool insert(Movie* m);              // insert m; merge stock if key exists (non-Classic)
    Movie* find(const Movie& key) const; // return movie pointer or nullptr
    void inorderDisplay(std::ostream& out) const; // print all movies in sorted order
    void makeEmpty();                   // delete all nodes and their Movie objects

private:
    struct Node {
        Movie* data;   // heap-allocated Movie; owned by this node
        Node* left;
        Node* right;
        Node(Movie* m) : data(m), left(nullptr), right(nullptr) {}
    };

    Node* root;

    bool insertHelper(Node*& node, Movie* m);              // recursive insert
    Movie* findHelper(Node* node, const Movie& key) const; // recursive find
    void inorderHelper(Node* node, std::ostream& out) const; // recursive traversal
    void destroyTree(Node* node);                          // recursive delete
};
