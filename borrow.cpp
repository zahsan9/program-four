// -------------------------------- borrow.cpp ---------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the Borrow transaction. Validates the customer and movie,
//          decrements stock, and appends this transaction to customer history.
//          On success, ownership of this object transfers to the customer.
// ----------------------------------------------------------------------------

#include "borrow.h"
#include "store.h"
#include "customer.h"
#include "movie.h"
#include <iostream>

// --------------------------------- Borrow() ----------------------------------
// Default constructor.
// preconditions:  none
// postconditions: action = 'B'; genreCode, mediaType = ' '; keyMovie = nullptr
// ----------------------------------------------------------------------------
Borrow::Borrow() : genreCode(' '), mediaType(' '), keyMovie(nullptr) {
    action = 'B';
}

// --------------------------------- ~Borrow() ---------------------------------
// Destructor.
// preconditions:  none
// postconditions: keyMovie deleted if doTransaction never consumed it
// ----------------------------------------------------------------------------
Borrow::~Borrow() {
    delete keyMovie;
}

// --------------------------------- setData() ---------------------------------
// Parses the command fields after the action character.
// preconditions:  in holds "customerID mediaType genreCode <search key fields>"
// postconditions: customerID, mediaType, genreCode, and keyMovie populated;
//                 keyMovie is nullptr if genreCode is unrecognized
// ----------------------------------------------------------------------------
void Borrow::setData(std::istream& in) {
    in >> customerID >> mediaType >> genreCode;
    keyMovie = Store::makeMovie(genreCode);
    if (keyMovie)
        keyMovie->setSearchKey(in);
}

// ------------------------------ doTransaction() ------------------------------
// Validates and executes the borrow: decrements stock and records history.
// preconditions:  setData() has been called; s is a valid store
// postconditions: on success, stock decremented by 1, this transaction appended
//                 to customer history, and returns true; on any failure, an
//                 error is printed to stderr and returns false
// ----------------------------------------------------------------------------
bool Borrow::doTransaction(Store& s) {
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
    if (!found->borrow()) {
        std::cerr << "ERROR: Out of stock: ";
        found->displayBrief(std::cerr);
        std::cerr << "\n";
        if (genreCode == 'C') {
            Movie* alt = s.findClassicAlternative(found->getTitle());
            if (alt) {
                std::cerr << "  Suggestion: ";
                alt->displayBrief(std::cerr);
                std::cerr << " (" << alt->getStock() << " available)\n";
            }
        }
        return false;
    }
    movie = found;
    delete keyMovie;
    keyMovie = nullptr;
    cust->addTransaction(this);
    return true;
}

// --------------------------------- display() ---------------------------------
// Outputs the transaction label and brief movie description.
// preconditions:  none
// postconditions: writes "Borrow  <brief movie>" to out; out unchanged
// ----------------------------------------------------------------------------
void Borrow::display(std::ostream& out) const {
    out << "Borrow  ";
    if (movie)
        movie->displayBrief(out);
}
