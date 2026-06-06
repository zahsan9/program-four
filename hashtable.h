#pragma once
#include "customer.h"

class HashTable {
public:
    HashTable();

    void insert(const Customer& c);
    Customer* find(int id);

private:
    static const int TABLE_SIZE = 53;

    Customer table[TABLE_SIZE];
    bool occupied[TABLE_SIZE];
};
