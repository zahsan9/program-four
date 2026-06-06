#pragma once
#include "transaction.h"

class HistoryTxn : public Transaction {
public:
    HistoryTxn();
    bool doTransaction(Store& s) override;
    void setData(std::istream& in) override;
    void display(std::ostream& out) const override;
};
