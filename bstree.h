#pragma once
#include <iostream>
#include "movie.h"

class BSTree {
public:
    BSTree();
    ~BSTree();

    bool insert(Movie* m);
    Movie* find(const Movie& key) const;
    void inorderDisplay(std::ostream& out) const;
    void makeEmpty();

private:
    struct Node {
        Movie* data;
        Node* left;
        Node* right;
        Node(Movie* m) : data(m), left(nullptr), right(nullptr) {}
    };

    Node* root;

    bool insertHelper(Node*& node, Movie* m);
    Movie* findHelper(Node* node, const Movie& key) const;
    void inorderHelper(Node* node, std::ostream& out) const;
    void destroyTree(Node* node);
};
