#pragma once
#include "transaction.h"

class ReturnTxn : public Transaction {
public:
    ReturnTxn();
    ~ReturnTxn() override;

    bool doTransaction(Store& s) override;
    void setData(std::istream& in) override;
    void display(std::ostream& out) const override;

private:
    char genreCode;
    char mediaType;
    Movie* keyMovie;
};
