// ----------------------------- inventory_txn.cpp -----------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the InventoryTxn transaction. Traverses all three genre
//          BSTrees in sorted order and prints each movie's full inventory line.
// ----------------------------------------------------------------------------

#include "inventory_txn.h"
#include "store.h"
#include <iostream>

// ------------------------------ InventoryTxn() -------------------------------
// Default constructor.
// preconditions:  none
// postconditions: action = 'I'
// ----------------------------------------------------------------------------
InventoryTxn::InventoryTxn() { action = 'I'; }

// --------------------------------- setData() ---------------------------------
// No-op: Inventory requires no additional command fields.
// preconditions:  none
// postconditions: stream and state unchanged
// ----------------------------------------------------------------------------
void InventoryTxn::setData(std::istream& /*in*/) {}

// ------------------------------ doTransaction() ------------------------------
// Prints every movie in all three genre trees, each tree in sorted order.
// preconditions:  s is a fully loaded store
// postconditions: all movies printed to stdout with genre section headers;
//                 store state unchanged; always returns true
// ----------------------------------------------------------------------------
bool InventoryTxn::doTransaction(Store& s) {
    std::cout << "Comedies:\n";
    s.getComedyTree().inorderDisplay(std::cout);
    std::cout << "\nDramas:\n";
    s.getDramaTree().inorderDisplay(std::cout);
    std::cout << "\nClassics:\n";
    s.getClassicTree().inorderDisplay(std::cout);
    std::cout << "\n";
    return true;
}

// --------------------------------- display() ---------------------------------
// Outputs the transaction label.
// preconditions:  none
// postconditions: writes "Inventory" to out; out unchanged
// ----------------------------------------------------------------------------
void InventoryTxn::display(std::ostream& out) const {
    out << "Inventory";
}
