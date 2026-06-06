#include "return_txn.h"
#include "store.h"
#include "customer.h"
#include "movie.h"
#include <iostream>

ReturnTxn::ReturnTxn() : genreCode(' '), mediaType(' '), keyMovie(nullptr) {
    action = 'R';
}

ReturnTxn::~ReturnTxn() {
    delete keyMovie;
}

void ReturnTxn::setData(std::istream& in) {
    in >> customerID >> mediaType >> genreCode;
    keyMovie = Store::makeMovie(genreCode);
    if (keyMovie)
        keyMovie->setSearchKey(in);
}

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

void ReturnTxn::display(std::ostream& out) const {
    out << "Return   ";
    if (movie)
        movie->displayBrief(out);
}
