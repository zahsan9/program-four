// ------------------------------ return_txn.cpp -------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the ReturnTxn transaction. Validates the customer and
//          movie, checks that the customer has an outstanding borrow, increments
//          stock, and appends this transaction to customer history.
//          On success, ownership of this object transfers to the customer.
// ----------------------------------------------------------------------------

#include "return_txn.h"
#include "store.h"
#include "customer.h"
#include "movie.h"
#include <iostream>

// -------------------------------- ReturnTxn() --------------------------------
// Default constructor.
// preconditions:  none
// postconditions: action = 'R'; genreCode, mediaType = ' '; keyMovie = nullptr
// ----------------------------------------------------------------------------
ReturnTxn::ReturnTxn() : genreCode(' '), mediaType(' '), keyMovie(nullptr) {
    action = 'R';
}

// -------------------------------- ~ReturnTxn() -------------------------------
// Destructor.
// preconditions:  none
// postconditions: keyMovie deleted if doTransaction never consumed it
// ----------------------------------------------------------------------------
ReturnTxn::~ReturnTxn() {
    delete keyMovie;
}

// --------------------------------- setData() ---------------------------------
// Parses the command fields after the action character.
// preconditions:  in holds "customerID mediaType genreCode <search key fields>"
// postconditions: customerID, mediaType, genreCode, and keyMovie populated;
//                 keyMovie is nullptr if genreCode is unrecognized
// ----------------------------------------------------------------------------
void ReturnTxn::setData(std::istream& in) {
    in >> customerID >> mediaType >> genreCode;
    keyMovie = Store::makeMovie(genreCode);
    if (keyMovie)
        keyMovie->setSearchKey(in);
}

// ------------------------------ doTransaction() ------------------------------
// Validates and executes the return: checks outstanding borrow then increments stock.
// preconditions:  setData() has been called; s is a valid store
// postconditions: on success, stock incremented by 1, this transaction appended
//                 to customer history, and returns true; on any failure, an
//                 error is printed to stderr and returns false
// ----------------------------------------------------------------------------
bool ReturnTxn::doTransaction(Store& s) {
    if (!keyMovie) {
        std::cerr << "ERROR: Invalid movie type '" << genreCode
                  << "' — discarding command\n";
        return false;
    }
    Customer* cust = s.findCustomer(customerID);
    if (!cust) {
        std::cerr << "ERROR: Customer " << customerID
                  << " not found — discarding command\n";
        return false;
    }
    Movie* found = s.findMovie(genreCode, *keyMovie);
    if (!found) {
        std::cerr << "ERROR: Movie not in inventory: ";
        keyMovie->displayBrief(std::cerr);
        std::cerr << "\n";
        return false;
    }
    if (!cust->hasOutstanding(found)) {
        std::cerr << "ERROR: Customer " << customerID
                  << " never borrowed: ";
        found->displayBrief(std::cerr);
        std::cerr << "\n";
        return false;
    }
    found->returnCopy();
    movie = found;
    delete keyMovie;
    keyMovie = nullptr;
    cust->addTransaction(this);
    return true;
}

// --------------------------------- display() ---------------------------------
// Outputs the transaction label and brief movie description.
// preconditions:  none
// postconditions: writes "Return   <brief movie>" to out; out unchanged
// ----------------------------------------------------------------------------
void ReturnTxn::display(std::ostream& out) const {
    out << "Return   ";
    if (movie)
        movie->displayBrief(out);
}
