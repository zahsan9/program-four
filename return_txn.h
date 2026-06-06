// ------------------------------- return_txn.h --------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares the ReturnTxn transaction subclass (action code 'R'). A
//          Return verifies an outstanding borrow, increments stock by one, and
//          records the transaction in the customer's history.
// ----------------------------------------------------------------------------

#pragma once
#include "transaction.h"

class ReturnTxn : public Transaction {
public:
    ReturnTxn();
    ~ReturnTxn() override;  // deletes keyMovie if doTransaction never ran

    bool doTransaction(Store& s) override;   // verify outstanding borrow, increment stock
    void setData(std::istream& in) override;  // parse customerID, mediaType, genre, search key
    void display(std::ostream& out) const override; // writes "Return   <brief movie>"

private:
    char genreCode;   // genre of the movie being returned
    char mediaType;   // media format (parsed but not used; only DVD is supported)
    Movie* keyMovie;  // temporary search key; deleted after successful lookup
};
