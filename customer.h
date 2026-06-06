// -------------------------------- customer.h ---------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares the Customer class. Each customer has a unique 4-digit ID
//          and owns an ordered list of all their Transaction objects. The
//          destructor is responsible for deleting all transactions in history.
// ----------------------------------------------------------------------------

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
    ~Customer();  // deletes all Transaction* in history

    void addTransaction(Transaction* txn);                 // append txn to history
    void printHistoryReverse(std::ostream& out) const;     // print history newest-first
    bool hasOutstanding(const Movie* m) const;             // true if net borrows > 0

    int getID() const { return id; }
    std::string getLastName() const { return lastName; }
    std::string getFirstName() const { return firstName; }
    bool isValid() const { return id != -1; }  // default-constructed customers are invalid

private:
    int id;                           // 4-digit unique customer identifier (-1 if invalid)
    std::string lastName;
    std::string firstName;
    std::vector<Transaction*> history; // transactions in chronological order; owned by Customer
};
