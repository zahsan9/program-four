#include "borrow.h"
#include "store.h"
#include "customer.h"
#include "movie.h"
#include <iostream>

Borrow::Borrow() : genreCode(' '), mediaType(' '), keyMovie(nullptr) {
    action = 'B';
}

Borrow::~Borrow() {
    delete keyMovie;
}

void Borrow::setData(std::istream& in) {
    in >> customerID >> mediaType >> genreCode;
    keyMovie = Store::makeMovie(genreCode);
    if (keyMovie)
        keyMovie->setSearchKey(in);
}

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
        return false;
    }
    movie = found;
    delete keyMovie;
    keyMovie = nullptr;
    cust->addTransaction(this);
    return true;
}

void Borrow::display(std::ostream& out) const {
    out << "Borrow  ";
    if (movie)
        movie->displayBrief(out);
}
