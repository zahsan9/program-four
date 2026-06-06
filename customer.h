#pragma once
#include <iostream>
#include <string>
#include <vector>

class Movie;
class Transaction;

class Customer {
public:
    Customer();
    Customer(int id, const std::string& last, const std::string& first);
    ~Customer();

    void addTransaction(Transaction* txn);
    void printHistoryReverse(std::ostream& out) const;
    bool hasOutstanding(const Movie* m) const;

    int getID() const { return id; }
    std::string getLastName() const { return lastName; }
    std::string getFirstName() const { return firstName; }
    bool isValid() const { return id != -1; }

private:
    int id;
    std::string lastName;
    std::string firstName;
    std::vector<Transaction*> history;
};
