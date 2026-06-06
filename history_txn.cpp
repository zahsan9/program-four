#include "history_txn.h"
#include "store.h"
#include "customer.h"
#include <iostream>

HistoryTxn::HistoryTxn() { action = 'H'; }

void HistoryTxn::setData(std::istream& in) {
    in >> customerID;
}

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

void HistoryTxn::display(std::ostream& out) const {
    out << "History " << customerID;
}
