#pragma once
#include <iostream>

class Store;
class Movie;

class Transaction {
public:
    Transaction();
    virtual ~Transaction() = default;

    virtual bool doTransaction(Store& s) = 0;
    virtual void setData(std::istream& in) = 0;
    virtual void display(std::ostream& out) const = 0;

    char getAction() const { return action; }
    Movie* getMovie() const { return movie; }

protected:
    int customerID;
    char action;
    Movie* movie;
};
