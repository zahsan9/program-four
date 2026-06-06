// ------------------------------- customer.cpp --------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the Customer class. Manages a customer's identity and
//          their ordered transaction history, including borrow tracking needed
//          to validate return operations.
// ----------------------------------------------------------------------------

#include "customer.h"
#include "transaction.h"
#include "movie.h"

// -------------------------------- Customer() ---------------------------------
// Default constructor. Produces an invalid sentinel customer.
// preconditions:  none
// postconditions: id = -1; isValid() == false; history empty
// ----------------------------------------------------------------------------
Customer::Customer() : id(-1) {}

// -------------------- Customer(int, string, string) --------------------------
// Parameterized constructor.
// preconditions:  id is a valid 4-digit customer identifier
// postconditions: id, lastName, and firstName set; history empty
// ----------------------------------------------------------------------------
Customer::Customer(int id, const std::string& last, const std::string& first)
    : id(id), lastName(last), firstName(first) {}

// -------------------------------- ~Customer() --------------------------------
// Destructor.
// preconditions:  none
// postconditions: all Transaction* in history deleted; memory freed
// ----------------------------------------------------------------------------
Customer::~Customer() {
    for (Transaction* t : history)
        delete t;
}

// ------------------------------ addTransaction() -----------------------------
// Appends a transaction to the end of history.
// preconditions:  txn is a valid, heap-allocated Transaction; ownership transfers
// postconditions: txn appended to history; history size increased by 1
// ----------------------------------------------------------------------------
void Customer::addTransaction(Transaction* txn) {
    history.push_back(txn);
}

// --------------------------- printHistoryReverse() ---------------------------
// Prints this customer's header and all transactions in reverse chronological order.
// preconditions:  none
// postconditions: customer header and each transaction written to out;
//                 history unchanged
// ----------------------------------------------------------------------------
void Customer::printHistoryReverse(std::ostream& out) const {
    out << "Customer " << id << " " << lastName << " " << firstName << ":\n";
    for (int i = (int)history.size() - 1; i >= 0; --i) {
        history[i]->display(out);
        out << "\n";
    }
}

// ------------------------------ hasOutstanding() -----------------------------
// Returns true if the customer currently holds at least one copy of movie m.
// preconditions:  m is a valid Movie pointer that exists in the BSTree
// postconditions: history unchanged; counts net borrows (Borrow +1, Return -1)
//                 for the exact movie pointer and returns count > 0
// ----------------------------------------------------------------------------
bool Customer::hasOutstanding(const Movie* m) const {
    int count = 0;
    for (const Transaction* t : history) {
        if (t->getMovie() == m) {
            if (t->getAction() == 'B') ++count;
            else if (t->getAction() == 'R') --count;
        }
    }
    return count > 0;
}
