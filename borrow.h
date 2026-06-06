// --------------------------------- borrow.h ----------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares the Borrow transaction subclass (action code 'B'). A Borrow
//          reduces a movie's stock by one and records the transaction in the
//          customer's history.
// ----------------------------------------------------------------------------

#pragma once
#include "transaction.h"
#include <string>

class Borrow : public Transaction {
public:
    Borrow();
    ~Borrow() override;  // deletes keyMovie if doTransaction never ran

    bool doTransaction(Store& s) override;  // find movie, decrement stock, record history
    void setData(std::istream& in) override; // parse customerID, mediaType, genre, search key
    void display(std::ostream& out) const override; // writes "Borrow  <brief movie>"

private:
    char genreCode;   // genre of the movie being borrowed
    char mediaType;   // media format (parsed but not used; only DVD is supported)
    Movie* keyMovie;  // temporary search key; deleted after successful lookup
};
