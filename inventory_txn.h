// ------------------------------ inventory_txn.h ------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares the InventoryTxn transaction subclass (action code 'I').
//          Inventory prints all three genre BSTrees in sorted order.
// ----------------------------------------------------------------------------

#pragma once
#include "transaction.h"

class InventoryTxn : public Transaction {
public:
    InventoryTxn();
    bool doTransaction(Store& s) override;   // print all three genre trees in order
    void setData(std::istream& in) override;  // no-op: Inventory takes no additional fields
    void display(std::ostream& out) const override; // writes "Inventory"
};
