// ------------------------------ history_txn.cpp ------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the HistoryTxn transaction. Looks up the customer by ID
//          and delegates to Customer::printHistoryReverse to print their
//          transaction list from most recent to oldest.
// ----------------------------------------------------------------------------

#include "history_txn.h"
#include "store.h"
#include "customer.h"
#include <iostream>

// ------------------------------- HistoryTxn() --------------------------------
// Default constructor.
// preconditions:  none
// postconditions: action = 'H'
// ----------------------------------------------------------------------------
HistoryTxn::HistoryTxn() { action = 'H'; }

// --------------------------------- setData() ---------------------------------
// Parses the command fields after the action character.
// preconditions:  in holds " customerID"
// postconditions: customerID populated from stream
// ----------------------------------------------------------------------------
void HistoryTxn::setData(std::istream& in) {
    in >> customerID;
}

// ------------------------------ doTransaction() ------------------------------
// Looks up the customer and prints their transaction history most recent first.
// preconditions:  setData() has been called; s is a valid store
// postconditions: on success, customer history printed to stdout and returns true;
//                 if customer not found, error printed to stderr and returns false
// ----------------------------------------------------------------------------
bool HistoryTxn::doTransaction(Store& s) {
    Customer* cust = s.findCustomer(customerID);
    if (!cust) {
        std::cerr << "ERROR: Customer " << customerID
                  << " not found — discarding command\n";
        return false;
    }
    cust->printHistoryReverse(std::cout);
    return true;
}

// --------------------------------- display() ---------------------------------
// Outputs the transaction label and customer ID.
// preconditions:  none
// postconditions: writes "History <customerID>" to out; out unchanged
// ----------------------------------------------------------------------------
void HistoryTxn::display(std::ostream& out) const {
    out << "History " << customerID;
}
