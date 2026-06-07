// -------------------------------- bstree.cpp ---------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the BSTree. Genre-specific sort order is provided by each
//          Movie subclass's operator< and operator==, so this tree is reused for
//          Comedy, Drama, and Classic without modification.
// ----------------------------------------------------------------------------

#include "bstree.h"

// --------------------------------- BSTree() ----------------------------------
// Default constructor.
// preconditions:  none
// postconditions: empty tree; root = nullptr
// ----------------------------------------------------------------------------
BSTree::BSTree() : root(nullptr) {}

// --------------------------------- ~BSTree() ---------------------------------
// Destructor.
// preconditions:  none
// postconditions: all nodes and their Movie objects deleted; memory freed
// ----------------------------------------------------------------------------
BSTree::~BSTree() { makeEmpty(); }

// ---------------------------------- insert() ---------------------------------
// Inserts m into the tree, or merges its stock into the existing node if the key
// already exists. The caller loses ownership of m on a merge (it is deleted here).
// preconditions:  m is a heap-allocated Movie; caller transfers ownership
// postconditions: if key is new, a new node holds m and returns true;
//                 if key exists, existing node's stock += m->getStock(),
//                 m is deleted, and returns false
// ----------------------------------------------------------------------------
bool BSTree::insert(Movie* m) {
    return insertHelper(root, m);
}

// ----------------------------------- find() ----------------------------------
// Searches for a movie that compares equal to key.
// preconditions:  key fields are set (via setSearchKey)
// postconditions: returns pointer to the matching Movie in the tree, or nullptr
//                 if no match exists; tree unchanged
// ----------------------------------------------------------------------------
Movie* BSTree::find(const Movie& key) const {
    return findHelper(root, key);
}

// ------------------------------ inorderDisplay() -----------------------------
// Prints every movie in sorted order by calling Movie::display on each node.
// preconditions:  none
// postconditions: all movies written to out in ascending sort order; tree unchanged
// ----------------------------------------------------------------------------
void BSTree::inorderDisplay(std::ostream& out) const {
    inorderHelper(root, out);
}

// --------------------------------- makeEmpty() -------------------------------
// Deletes all nodes and the Movie objects they own.
// preconditions:  none
// postconditions: tree is empty; root = nullptr; all heap memory freed
// ----------------------------------------------------------------------------
void BSTree::makeEmpty() {
    destroyTree(root);
    root = nullptr;
}

// --------------------------------- findAlt() ---------------------------------
// Returns the first in-stock movie whose title matches, or nullptr if none.
// preconditions:  none
// postconditions: tree unchanged; returns pointer into tree or nullptr
// ----------------------------------------------------------------------------
Movie* BSTree::findAlt(const std::string& title) const {
    return findAltHelper(root, title);
}

// =============================================================================

bool BSTree::insertHelper(Node*& node, Movie* m) {
    if (!node) {
        node = new Node(m);
        return true;
    }
    if (*m == *node->data) {  // duplicate key: merge stock, discard m
        node->data->addStock(m->getStock());
        delete m;
        return false;
    }
    if (*m < *node->data)
        return insertHelper(node->left, m);
    return insertHelper(node->right, m);
}

Movie* BSTree::findHelper(Node* node, const Movie& key) const {
    if (!node) return nullptr;
    if (!(key < *node->data) && !(*node->data < key))  // neither less: must be equal
        return node->data;
    if (key < *node->data)
        return findHelper(node->left, key);
    return findHelper(node->right, key);
}

Movie* BSTree::findAltHelper(Node* node, const std::string& title) const {
    if (!node) return nullptr;
    Movie* left = findAltHelper(node->left, title);
    if (left) return left;
    if (node->data->getTitle() == title && node->data->getStock() > 0)
        return node->data;
    return findAltHelper(node->right, title);
}

void BSTree::inorderHelper(Node* node, std::ostream& out) const {
    if (!node) return;
    inorderHelper(node->left, out);
    node->data->display(out);
    out << "\n";
    inorderHelper(node->right, out);
}

void BSTree::destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node->data;
    delete node;
}
