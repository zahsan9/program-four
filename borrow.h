#pragma once
#include "transaction.h"
#include <string>

class Borrow : public Transaction {
public:
    Borrow();
    ~Borrow() override;

    bool doTransaction(Store& s) override;
    void setData(std::istream& in) override;
    void display(std::ostream& out) const override;

private:
    char genreCode;
    char mediaType;
    Movie* keyMovie;
};
