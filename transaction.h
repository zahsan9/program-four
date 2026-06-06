// ------------------------------- transaction.h -------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares the abstract Transaction base class. Subclasses (Borrow,
//          ReturnTxn, InventoryTxn, HistoryTxn) implement doTransaction() to
//          carry out their respective store operations.
// ----------------------------------------------------------------------------

#pragma once
#include <iostream>

class Store;
class Movie;

class Transaction {
public:
    Transaction();
    virtual ~Transaction() = default;

    virtual bool doTransaction(Store& s) = 0;        // execute this transaction on the store
    virtual void setData(std::istream& in) = 0;      // parse remaining command fields
    virtual void display(std::ostream& out) const = 0; // used by customer history output

    char getAction() const { return action; }   // 'B', 'R', 'I', or 'H'
    Movie* getMovie() const { return movie; }   // nullptr for Inventory and History

protected:
    int customerID;  // 4-digit customer identifier (0 for Inventory)
    char action;     // action code character
    Movie* movie;    // pointer to the movie acted on; owned by BSTree, not this object
};
