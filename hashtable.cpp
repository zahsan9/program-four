// ------------------------------- hashtable.cpp -------------------------------
// Nandini Mistry & Zainab Ahsan   CSS 343
// Created:  2026-05-24
// Modified: 2026-06-06
// ----------------------------------------------------------------------------
// Purpose: Implements the HashTable for Customer lookup. Quadratic probing
//          sequence: slot = (id % TABLE_SIZE + i*i) % TABLE_SIZE for i = 0..52.
// ----------------------------------------------------------------------------

#include "hashtable.h"

// -------------------------------- HashTable() --------------------------------
// Default constructor.
// preconditions:  none
// postconditions: all TABLE_SIZE slots marked unoccupied
// ----------------------------------------------------------------------------
HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i)
        occupied[i] = false;
}

// ---------------------------------- insert() ---------------------------------
// Inserts a copy of customer c into the first available slot.
// preconditions:  table is not full (at most TABLE_SIZE - 1 customers inserted)
// postconditions: a copy of c stored in the slot found by quadratic probing;
//                 occupied flag for that slot set to true
// ----------------------------------------------------------------------------
void HashTable::insert(const Customer& c) {
    int id = c.getID();
    for (int i = 0; i < TABLE_SIZE; ++i) {
        int slot = (id % TABLE_SIZE + i * i) % TABLE_SIZE;
        if (!occupied[slot]) {
            table[slot] = c;
            occupied[slot] = true;
            return;
        }
    }
}

// ----------------------------------- find() ----------------------------------
// Searches for a customer by ID using the same quadratic probing sequence.
// preconditions:  none
// postconditions: returns pointer to the Customer in the table if found;
//                 returns nullptr if an empty slot is encountered or after a
//                 full probe sequence
// ----------------------------------------------------------------------------
Customer* HashTable::find(int id) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        int slot = (id % TABLE_SIZE + i * i) % TABLE_SIZE;
        if (!occupied[slot]) return nullptr;
        if (table[slot].getID() == id) return &table[slot];
    }
    return nullptr;
}
