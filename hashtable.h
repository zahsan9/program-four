// -------------------------------- hashtable.h --------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Declares a fixed-size hash table for Customer objects, keyed on the
//          4-digit customer ID. Uses open addressing with quadratic probing and
//          a prime table size of 53 to minimize clustering.
// ----------------------------------------------------------------------------

#pragma once
#include "customer.h"

class HashTable {
public:
    HashTable();  // initializes all slots as unoccupied

    void insert(const Customer& c);  // probe for an open slot and copy c into it
    Customer* find(int id);          // return pointer to Customer or nullptr if not found

private:
    static const int TABLE_SIZE = 53; // prime size; hash function: id % TABLE_SIZE

    Customer table[TABLE_SIZE];       // inline Customer storage; no heap allocation per slot
    bool occupied[TABLE_SIZE];        // true if the corresponding slot holds a customer
};
