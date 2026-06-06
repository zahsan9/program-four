#include "customer.h"
#include "transaction.h"
#include "movie.h"

Customer::Customer() : id(-1) {}

Customer::Customer(int id, const std::string& last, const std::string& first)
    : id(id), lastName(last), firstName(first) {}

Customer::~Customer() {
    for (Transaction* t : history)
        delete t;
}

void Customer::addTransaction(Transaction* txn) {
    history.push_back(txn);
}

void Customer::printHistoryReverse(std::ostream& out) const {
    out << "Customer " << id << " " << lastName << " " << firstName << ":\n";
    for (int i = (int)history.size() - 1; i >= 0; --i) {
        history[i]->display(out);
        out << "\n";
    }
}

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
