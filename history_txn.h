// ------------------------------- history_txn.h -------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares the HistoryTxn transaction subclass (action code 'H').
//          History prints one customer's transaction list, most recent first.
// ----------------------------------------------------------------------------

#pragma once
#include "transaction.h"

class HistoryTxn : public Transaction {
public:
    HistoryTxn();
    bool doTransaction(Store& s) override;   // look up customer and print history
    void setData(std::istream& in) override;  // parse customerID
    void display(std::ostream& out) const override; // writes "History <customerID>"
};
