#include "bstree.h"

BSTree::BSTree() : root(nullptr) {}

BSTree::~BSTree() { makeEmpty(); }

bool BSTree::insert(Movie* m) {
    return insertHelper(root, m);
}

bool BSTree::insertHelper(Node*& node, Movie* m) {
    if (!node) {
        node = new Node(m);
        return true;
    }
    if (*m == *node->data) {
        node->data->addStock(m->getStock());
        delete m;
        return false;
    }
    if (*m < *node->data)
        return insertHelper(node->left, m);
    return insertHelper(node->right, m);
}

Movie* BSTree::find(const Movie& key) const {
    return findHelper(root, key);
}

Movie* BSTree::findHelper(Node* node, const Movie& key) const {
    if (!node) return nullptr;
    if (!(key < *node->data) && !(*node->data < key))
        return node->data;
    if (key < *node->data)
        return findHelper(node->left, key);
    return findHelper(node->right, key);
}

void BSTree::inorderDisplay(std::ostream& out) const {
    inorderHelper(root, out);
}

void BSTree::inorderHelper(Node* node, std::ostream& out) const {
    if (!node) return;
    inorderHelper(node->left, out);
    node->data->display(out);
    out << "\n";
    inorderHelper(node->right, out);
}

void BSTree::makeEmpty() {
    destroyTree(root);
    root = nullptr;
}

void BSTree::destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node->data;
    delete node;
}
