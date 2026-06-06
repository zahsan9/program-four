#include "inventory_txn.h"
#include "store.h"
#include <iostream>

InventoryTxn::InventoryTxn() { action = 'I'; }

void InventoryTxn::setData(std::istream& /*in*/) {}

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

void InventoryTxn::display(std::ostream& out) const {
    out << "Inventory";
}
