#pragma once
#include "transaction.h"

class InventoryTxn : public Transaction {
public:
    InventoryTxn();
    bool doTransaction(Store& s) override;
    void setData(std::istream& in) override;
    void display(std::ostream& out) const override;
};
